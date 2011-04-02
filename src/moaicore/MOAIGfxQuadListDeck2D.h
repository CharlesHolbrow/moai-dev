// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGFXQUADLISTDECK2D_H
#define	MOAIGFXQUADLISTDECK2D_H

#include <moaicore/MOAIDeck2D.h>

class MOAITexture;

//================================================================//
// USSpriteUVRect
//================================================================//
class USSpriteUVRect {
private:

	friend class MOAIGfxQuadListDeck2D;

	USRect	mRect;
	u32		mTransform;
};

//================================================================//
// USSpritePrim
//================================================================//
class USSpritePrim {
private:

	friend class MOAIGfxQuadListDeck2D;

	u32		mUVRectID;
	u32		mQuadID;
};

//================================================================//
// USSprite
//================================================================//
class USSprite {
private:

	friend class MOAIGfxQuadListDeck2D;

	u32		mBasePrim;
	u32		mTotalPrims;
};

//================================================================//
// MOAIGfxQuadListDeck2D
//================================================================//
/**	@brief Sprite library class.
*/
class MOAIGfxQuadListDeck2D :
	public MOAIDeck2D {
private:

	USRef < MOAITexture >			mTexture;
	
	USLeanArray < USSpriteUVRect >	mUVRects;
	USLeanArray < USQuad >			mQuads;
	USLeanArray < USSpritePrim >	mPrims;
	USLeanArray < USSprite >		mSprites;
	
	//----------------------------------------------------------------//
	static int	_bind					( lua_State* L );
	static int	_enumSprites			( lua_State* L );
	static int	_enumUVTiles			( lua_State* L );
	static int	_releaseTexture			( lua_State* L );
	static int	_reserveLists			( lua_State* L );
	static int	_reservePrims			( lua_State* L );
	static int	_reserveQuads			( lua_State* L );
	static int	_reserveUVRects			( lua_State* L );
	static int	_scaleCoords			( lua_State* L );
	static int	_scaleUVCoords			( lua_State* L );
	static int	_setList				( lua_State* L );
	static int	_setPrim				( lua_State* L );
	static int	_setQuad				( lua_State* L );
	static int	_setRect				( lua_State* L );
	static int	_setTexture				( lua_State* L );
	static int	_setUVRect				( lua_State* L );
	static int	_setUVRectTransform		( lua_State* L );

public:
	
	DECL_LUA_FACTORY ( MOAIGfxQuadListDeck2D )
	
	enum {
		UV_NONE,
		UV_ROTATE_90,
	};
	
	//----------------------------------------------------------------//
	bool			Bind					();
	bool			Contains				( u32 idx, const USVec2D& vec );
	void			Draw					( u32 idx, float xOff, float yOff, float xScale, float yScale );
	USRect			GetBounds				( u32 idx );
					MOAIGfxQuadListDeck2D	();
					~MOAIGfxQuadListDeck2D	();
	void			RegisterLuaClass		( USLuaState& state );
	void			RegisterLuaFuncs		( USLuaState& state );
	void			ReleaseTexture			();
	void			ReserveLists			( u32 total );
	void			ReservePrims			( u32 total );
	void			ReserveQuads			( u32 total );
	void			ReserveUVRects			( u32 total );
	void			SetList					( u32 idx, u32 basePrimID, u32 totalPrims );
	void			SetPrim					( u32 idx, u32 uvRectID, u32 screenRectID );
	void			SetQuad					( u32 idx, USQuad& quad );
	void			SetRect					( u32 idx, USRect& rect );
	void			SetUVRect				( u32 idx, USRect& rect );
	void			SetUVRectTransform		( u32 idx, u32 transform );
	STLString		ToString				();
};

#endif