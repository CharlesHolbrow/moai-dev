// Copyright (c) 2010-2012 Charles Holbrow
// http://www.PixelAether.com

#include "pch.h"
#include <math.h>
#include <moaicore/MOAIMapGrid.h>
#include <moaicore/MOAILogMessages.h>
#include <moaicore/MOAIAnimCurve.h>

//================================================================//
// MOAIFieldOfView
//================================================================//

//----------------------------------------------------------------//
bool* MOAIFieldOfView::Data () {

	return answer.Data();
}

//----------------------------------------------------------------//
bool MOAIFieldOfView::GetTile ( int x, int y ) {

	if ( x > mWidth || x < 0 ) return false;
	if ( y > mHeight || y < 0 ) return false;
	return answer [ y * mWidth + x ];
};

//----------------------------------------------------------------//
void MOAIFieldOfView::Init ( int width, int height ) {

	mWidth = width;
	mHeight = height;

	answer.Init ( width * height );
	answer.Fill ( false );
}

//----------------------------------------------------------------//
void MOAIFieldOfView::SetTile ( int x, int y, bool value ) {

	if ( x >= mWidth || x < 0 ) return;
	if ( y >= mHeight || y < 0 ) return;
	answer [ y * mWidth + x ] = value;
};

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	fieldOfView
	@text	Calculate the field of view from a grid position

	@in		MOAIMapGrid self
	@in		number xTile
	@in		number yTile
	@in		number mask
	@out	nil
*/
int MOAIMapGrid::_addLightSource ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIMapGrid, "UNNNU" )

	int xTile	= state.GetValue < int >( 2, 1 ) - 1;
	int yTile	= state.GetValue < int >( 3, 1 ) - 1;
	int radius	= state.GetValue < int >( 4, 1 );
	MOAIAnimCurve* curve = state.GetLuaObject < MOAIAnimCurve >( 5, 1 );
	
	self->AddLightSource ( xTile, yTile, radius, curve );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	fill
	@text	Set all tiles 8 bit value, preserving flags

	@in		MOAIGrid self
	@in		number value
	@out	nil
*/
int MOAIMapGrid::_fillLight ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIMapGrid, "UN" )

	u32 value	= state.GetValue < u32 >( 2, 1 );
	
	self->FillLight ( value );
	
	return 0;
}

//----------------------------------------------------------------//
bool MOAIMapGrid::AngleVisible ( float a, USLeanArray <float> * mins, USLeanArray <float> * maxes, int position ) {

	// iterate from position backwards
	for ( int i = position; i >= 0; i-- ) {

		if (	( a >= ( (*mins) [ i ] ) ) &&
				( a <= ( (*maxes) [ i ] ) ) )
			return false;
	};

	return true;
}

//----------------------------------------------------------------//
void MOAIMapGrid::GetAngles ( int xTile, int yTile, float & a2, float & a3 ) {

	float increment = 1.0f / ( ( yTile + 1.0f ) * 2.0f );

	a2 = ( ( xTile * 2 ) + 1 ) * increment;
	a3 = ( ( xTile + 1 ) * 2 ) * increment;
	
	if (xTile == yTile) a3 = 1.0f;

}

//----------------------------------------------------------------//
void MOAIMapGrid::FieldOfView ( int xTile, int yTile, int radius, MOAIFieldOfView * answer, char startOct, char endOct ) {

	// set the tile we are inspecting to visible 
	SetTile ( xTile, yTile, 0 );

	if ( radius <= 0 ) return;

	// Store min and maxes here:
	USLeanArray < float > mins;
	USLeanArray < float > maxes;

	mins.Init ( MAX_OBSTRUCTIONS );
	maxes.Init ( MAX_OBSTRUCTIONS );

	// How many obstructions have we found?
	// adjacent Obstructions should count as one
	int totalObstructions;
	int lineObstructions;
	
	// Count the number of visible tiles on the current line
	char visibleTileCount;
	bool lastLineEmpty = false;
	// Where in the array do we want to check from
	int arrayCheckPosition;

	// three angles for each tile
	float a1, a2, a3;

	// Which of the three angles are obstructed
	bool o1, o2, o3;

	// is the current tile opaque 
	bool opaque;

	// xy coords without adjusting for octant
	int x, y;
	// xy coords of the tile currently inspected
	int xOct;
	int yOct;

	// assume the answer array has been initialized

	for ( char oct = startOct; oct <= endOct; ++oct ) {

		totalObstructions = 0;

		// row and yPos are the same
		for ( int yPos = 1; yPos <= radius; yPos++ ) {

			lineObstructions = 0;
			visibleTileCount = 0;
			a3 = 0;

			for ( int xPos = 0; xPos <= yPos; xPos++ ) {

				// Find angles before octant calculation
				a1 = a3;
				GetAngles ( xPos, yPos, a2, a3 );

				arrayCheckPosition = totalObstructions - lineObstructions -1;
				o1 = AngleVisible ( a1, &mins, &maxes, arrayCheckPosition );
				o2 = AngleVisible ( a2, &mins, &maxes, arrayCheckPosition );
				o3 = AngleVisible ( a3, &mins, &maxes, arrayCheckPosition );

				// If At least one angle is visible, investigate tile
				if ( o1 || o2 || o3 ) {

					// first calculate the octant
					Octant ( xPos, yPos, oct, xOct, yOct );

					// get grid coordinates of the current tile on the grid
					x = xOct + xTile;
					y = yOct + yTile;

					opaque = Opaque ( x, y );

					// if the tile is opaque, mark it's angles as obstructed
					if ( opaque ) {

						//printf ( "Found Opaque tile at %2i, %2i\n", x, y );
						// check if we can extend the last entry
						if ( 
							( totalObstructions > 0 ) && 
							( maxes [ totalObstructions - 1 ] == a1 ) ) {

							//printf ( "Extending Entry: %5f, %4f\n", a1, a3);
							maxes [ totalObstructions - 1 ] = a3;

						// add a new range of angle obstruction
						} else {

							// TODO: check if we need to Grow the array
							//printf ( "Adding Entry: %5f, %4f\n", a1, a3);
							mins [ totalObstructions ] = a1;
							maxes [ totalObstructions ] = a3;
							totalObstructions++;
							lineObstructions++;
						};
					};

					// conditions for visibility
					if (
						( opaque && !lastLineEmpty ) ||
						( o1 && o2 ) || 
						( o2 && o3 ) ) {

						++visibleTileCount;
						
						// input to SetTile is relative to bottom left of answer
						( *answer ).SetTile ( xOct + radius, yOct + radius, true );

					}; // tile is visible
				}; // at lease one visible angle
			};// xPos
			
			lastLineEmpty = ( visibleTileCount == 0 );
		}; // yPos
	}; // octant
}

//----------------------------------------------------------------//
// Octants:
//   7  0
// 6      1
// 5      2
//   4  3
void MOAIMapGrid::Octant ( int x, int y, int o, int & xOut, int & yOut) {

	xOut = x * xxcomp [ o ] + y * xycomp [ o ];
	yOut = x * yxcomp [ o ] + y * yycomp [ o ];
}

int MOAIMapGrid::xxcomp[] = { 1, 0,  0,  1, -1,  0,  0, -1 };
int MOAIMapGrid::xycomp[] = { 0, 1,  1,  0,  0, -1, -1,  0 };
int MOAIMapGrid::yxcomp[] = { 0, 1, -1,  0,  0, -1,  1,  0 };
int MOAIMapGrid::yycomp[] = { 1, 0,  0, -1, -1,  0,  0,  1 };

//================================================================//
// MOAIMapGrid
//================================================================//

//----------------------------------------------------------------//
void MOAIMapGrid::AddLightSource ( int xTile, int yTile, int radius, MOAIAnimCurve* curve) {

	MOAICellCoord coord ( xTile, yTile );
	if ( !( this->IsValidCoord ( coord ) ) ) return;


	// Init Object for storing the VieldOfView
	int answerWidth = radius * 2 + 1;
	MOAIFieldOfView answer;
	answer.Init ( answerWidth, answerWidth );

	// Find which tiles are visible
	// populate the answer array
	FieldOfView ( xTile, yTile, radius, &answer, 0, 7 );

	// Iterate over the answer array
	bool * answerCursor = answer.Data ();

	int xStart = xTile - radius;
	int xEnd = xTile + radius;

	int yStart = yTile - radius;
	int yEnd = yTile + radius;

	for ( int yPos = yStart; yPos <= yEnd; yPos ++ ) {
		for ( int xPos = xStart; xPos <= xEnd; xPos ++ ) {
			
			if ( *answerCursor ) {

				int xDist = xTile - xPos;
				int yDist = yTile - yPos;

				float dist = sqrt ( (float) (xDist * xDist + yDist * yDist ) );
				float normalizedDist = dist / radius;

				float light = GetTileLight ( xPos, yPos );
				light += curve->GetValue ( normalizedDist );

				SetTileLight ( xPos, yPos, light );
			};
	
			++answerCursor;
		};
	};
}

//----------------------------------------------------------------//
void MOAIMapGrid::FillLight ( u32 value ) {

	if ( value >= 256 ) 
		printf ( "WARNING: MOAIMapGrid::FillLight - value > 256 - %i\n", value );

	FillPreservingFlags ( value, ~LIGHT_MASK ) ;
}

//----------------------------------------------------------------//
float MOAIMapGrid::GetTileLight ( int x, int y ) {

	MOAICellCoord coord ( x, y );
	if ( ! this->IsValidCoord ( coord ) ) return 0;

	u32 shadow = GetTile ( x, y ) & LIGHT_MASK;

	// take a shadow value between 0 and BLACK_INDEX 
	// convert it to a bright ness value between 0 and 1

	if ( shadow > BLACK_INDEX ) shadow = BLACK_INDEX;

	return 1.0f - ( float ( shadow ) / float ( BLACK_INDEX ) );
}

//----------------------------------------------------------------//
MOAIMapGrid::MOAIMapGrid () {
	
	RTTI_SINGLE ( MOAIGrid )
}

//----------------------------------------------------------------//
MOAIMapGrid::~MOAIMapGrid () {
}

//----------------------------------------------------------------//
bool MOAIMapGrid::Opaque ( int xTile, int yTile ) {

	u32 value = GetTile ( xTile, yTile );
	
	return ( ( value & TILE_OPAQUE ) == TILE_OPAQUE );
}

//----------------------------------------------------------------//
void MOAIMapGrid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "TILE_OBSTRUCT",			( u32 )TILE_OBSTRUCT );
	state.SetField ( -1, "TILE_OPAQUE",				( u32 )TILE_OPAQUE );
	state.SetField ( -1, "TILE_OBSTRUCT_OPAQUE",	( u32 )TILE_OBSTRUCT_OPAQUE );
	state.SetField ( -1, "BLACK_INDEX",				( u8 )BLACK_INDEX);

	MOAIGrid::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIMapGrid::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIGrid::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {

		{ "addLightSource",		_addLightSource },
		{ "fillLight",			_fillLight }, 
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIMapGrid::SetTileLight ( int x, int y, float brightness ) {

	u32 value = GetTile ( x, y ) & ~LIGHT_MASK;

	float shadow = 1 - brightness;

	if ( shadow > 1 ) shadow = 1;
	if ( shadow < 0 ) shadow = 0;

	// take a brightness value between 0 and 1 
	// convert it to a shadow value between 0 and BLACK_INDEX

	value = value +  u8 ( BLACK_INDEX * shadow ); 

	SetTile ( x, y, value );
}

