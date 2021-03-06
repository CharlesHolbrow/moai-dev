// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIMAPGRID_H
#define	MOAIMAPGRID_H

#include <moaicore/MOAIGrid.h>
#include <moaicore/MOAILua.h>
#include <moaicore/MOAIAnimCurve.h>

//================================================================//
// MOAIFieldOfView
//================================================================//
class MOAIFieldOfView {

private:

	//----------------------------------------------------------------//
	int					mWidth;
	int					mHeight;
	USLeanArray	<bool>	answer;

public:

	//----------------------------------------------------------------//
	GET ( int, Width, mWidth );
	GET ( int, Height, mHeight );

	//----------------------------------------------------------------//
	bool *				Data ();
	bool				GetTile ( int x, int y );
	void				Init ( int width, int height );
	void				SetTile ( int x, int y, bool value );
	
};

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
	static int		_addLightSource		( lua_State* L );
	static int		_fillLight			( lua_State* L );

	//----------------------------------------------------------------//
	bool			AngleVisible		( float a, USLeanArray <float> * mins, USLeanArray <float> * maxes, int loc );
	void			GetAngles			( int xTile, int yTile, float & a2, float & a3 );
	void			FieldOfView			( int xTile, int yTile, int radius, MOAIFieldOfView * answer, char startOct, char endOct );
	void			Octant				( int x, int y, int o, int & xOut, int & yOut );

	//----------------------------------------------------------------//
	static const int MAX_OBSTRUCTIONS = 30;
	static const int MAX_RADIUS = 20;
	static int xxcomp[8];
	static int xycomp[8];
	static int yxcomp[8];
	static int yycomp[8];


public:
	
	DECL_LUA_FACTORY ( MOAIMapGrid )
	
	//----------------------------------------------------------------//
					MOAIMapGrid			();
					~MOAIMapGrid		();
	void			AddLightSource		( int xTile, int yTile, int radius, MOAIAnimCurve* curve );
	bool			Opaque				( int xTile, int yTile );
	void			FillLight			( u32 value );

	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );

	void			SetTileLight		( int x, int y, float brightness );
	float			GetTileLight		( int x, int y );


	//----------------------------------------------------------------//
	static const u32 TILE_OBSTRUCT			= 0x20000000;
	static const u32 TILE_OPAQUE			= 0x40000000;
	
	static const u32 TILE_OBSTRUCT_OPAQUE	= 0x60000000;

	static const u32 FLAGS_MASK				= 0xf0000000;
	static const u32 LIGHT_MASK				= 0x000000ff;

	static const u8 BLACK_INDEX				= 24;

};

#endif
