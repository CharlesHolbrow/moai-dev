// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIMAPGRID_H
#define	MOAIMAPGRID_H

#include <moaicore/MOAIGrid.h>
#include <moaicore/MOAILua.h>

//================================================================//
// MOAIMapGrid
//================================================================//
/**	@name	MOAIMapGrid
	@text	Grid data object. Grid cells are indexed starting and (1,1).
			Grid indices will wrap if out of range.
*/
class MOAIMapGrid :
	public MOAIGrid {
private:

	//----------------------------------------------------------------//
	static int		_fieldOfView		( lua_State* L );

	//----------------------------------------------------------------//
	bool			AngleVisible		( float a, USLeanArray <float> * mins, USLeanArray <float> * maxes, int loc );
	void			GetAngles			( int xTile, int yTile, float & a2, float & a3 );
	void			Octant				( int x, int y, int o, int & xOut, int & yOut );

	//----------------------------------------------------------------//
	static const int MAX_OBSTRUCTIONS = 30;
	static int xxcomp[8];
	static int xycomp[8];
	static int yxcomp[8];
	static int yycomp[8];


public:
	
	DECL_LUA_FACTORY ( MOAIMapGrid )
	
	//----------------------------------------------------------------//
					MOAIMapGrid			();
					~MOAIMapGrid		();
	void			FieldOfView			( int xTile, int yTile, int radius, int startOct = 0, int endOct = 7 );
	bool			Opaque				( int xTile, int yTile );

	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );


	//----------------------------------------------------------------//
	static const u32 TILE_OBSTRUCT			= 0x20000000;
	static const u32 TILE_OPAQUE			= 0x40000000;
	
	static const u32 TILE_OBSTRUCT_OPAQUE	= 0x60000000;

	static const u32 FLAGS_MASK				= 0xf0000000;
	static const u32 CODE_MASK				= 0x0fffffff;

};

#endif
