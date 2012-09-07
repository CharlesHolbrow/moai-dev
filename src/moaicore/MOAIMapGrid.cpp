// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIMapGrid.h>
#include <moaicore/MOAILogMessages.h>
#include <moaicore/MOAIStream.h>

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
int MOAIMapGrid::_fieldOfView ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIMapGrid, "UNNN" )

	int xTile	= state.GetValue < int >( 2, 1 ) - 1;
	int yTile	= state.GetValue < int >( 3, 1 ) - 1;
	int radius	= state.GetValue < int >( 4, 1 );
	
	self->FieldOfView ( xTile, yTile, radius );
	
	return 0;
}

//----------------------------------------------------------------//
void MOAIMapGrid::GetAngles ( int xTile, int yTile, float & a2, float & a3 ) {

	float increment = 1.0f / ( ( yTile + 1.0f ) * 2.0f );

	a2 = ( ( xTile * 2 ) + 1 ) * increment;
	a3 = ( ( xTile + 1 ) * 2 ) * increment;
	
	if (xTile == yTile) a3 = 1.0f;

}

//----------------------------------------------------------------//
// Octants:
//   3  0
// 2      1
// 5      6
//   4  7
void MOAIMapGrid::Octant ( int x, int y, int o, int & xOut, int & yOut) {

	xOut = x * xxcomp [ o ] + y * xycomp [ o ];
	yOut = x * yxcomp [ o ] + y * yycomp [ o ];
}

int MOAIMapGrid::xxcomp[] = { 1, 0,  0, -1, -1,  0,  0,  1 };
int MOAIMapGrid::xycomp[] = { 0, 1, -1,  0,  0, -1,  1,  0 };
int MOAIMapGrid::yxcomp[] = { 0, 1,  1,  0,  0, -1, -1,  0 };
int MOAIMapGrid::yycomp[] = { 1, 0,  0,  1, -1,  0,  0, -1 };

//================================================================//
// MOAIMapGrid
//================================================================//

//----------------------------------------------------------------//
void MOAIMapGrid::FieldOfView ( int xTile, int yTile, int radius, int startOct, int endOct ) {

	MOAICellCoord coord ( xTile, yTile );
	if ( !( this->IsValidCoord ( coord ) ) ) return;

	// Sanity-check start and end octant
	if (	( startOct < 0 ) || 
			( endOct > 7 ) ||
			( startOct > endOct ) )
		return;

	// for testing only
	int i;

	// three angles for each tile
	float a1, a2, a3 = 0;

	// xy coords without adjusting for octant
	int x, y;
	// xy coords of the tile currently inspected
	int xOct;
	int yOct;

	i = 1;

	// row and yPos are the same
	for ( int yPos = 1; yPos <= radius; yPos++ ) {

		for ( int xPos = 0; xPos <= yPos; xPos++ ) {

			// Find angles before octant calculation
			a1 = a3;
			GetAngles ( xPos, yPos, a2, a3 );

			for ( int oct = startOct; oct <= endOct; ++oct ) {

				// first calculate the octant
				Octant ( xPos, yPos, oct, xOct, yOct );

				// then calculate the offset
				x = xOct + xTile;
				y = yOct + yTile;

				SetTile ( x, y, oct + 1 );

				printf ( "Tile (%2i, %2i): %5f %5f %5f\n", xTile, yTile, a1, a2, a3 );
				i++;

			};
		};
	};
}

//----------------------------------------------------------------//
MOAIMapGrid::MOAIMapGrid () {
	
//	RTTI_SINGLE ( MOAIGrid )
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIGrid )
		
	RTTI_END

}

//----------------------------------------------------------------//
MOAIMapGrid::~MOAIMapGrid () {
}

//----------------------------------------------------------------//
void MOAIMapGrid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "TILE_OBSTRUCT",			( u32 )TILE_OBSTRUCT );
	state.SetField ( -1, "TILE_OPAQUE",				( u32 )TILE_OPAQUE );
	state.SetField ( -1, "TILE_OBSTRUCT_OPAQUE",	( u32 )TILE_OBSTRUCT_OPAQUE );

	MOAIGrid::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIMapGrid::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIGrid::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {

		{ "fieldOfView",		_fieldOfView },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

