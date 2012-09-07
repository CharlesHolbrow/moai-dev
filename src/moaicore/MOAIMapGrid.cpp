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

	float increment = 1.0 / ( ( yTile + 1.0 ) * 2.0 );

	a2 = ( ( xTile * 2 ) + 1 ) * increment;
	a3 = ( ( xTile + 1 ) * 2 ) * increment;
	
	if (xTile == yTile) a3 = 1.0f;
	printf ( "Tile (%2i, %2i): %5f %5f\n", xTile, yTile, a2, a3 );
}

//================================================================//
// MOAIMapGrid
//================================================================//

//----------------------------------------------------------------//
void MOAIMapGrid::FieldOfView ( int xTile, int yTile, int radius ) {

	MOAICellCoord coord ( xTile, yTile );
	if ( !( this->IsValidCoord ( coord ) ) ) return;

	int i = 1;

	// three angles for each tile
	float a1 = 0;
	float a2, a3;

	// xy coords of the tile currently inspected
	int x;
	int y;

	// row and yPos are the same
	for ( int yPos = 1; yPos <= radius; yPos++ ) {

		for ( int xPos = 0; xPos <= yPos; xPos++ ) {

			// first calculate the octant
			// ...
			// then calculate the offset
			x = xPos + xTile;
			y = yPos + yTile;

			SetTile ( x, y, i );
			GetAngles ( xPos, yPos, a2, a3 );

			i++;

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

