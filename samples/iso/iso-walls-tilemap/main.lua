----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 640, 640 )

layer = MOAILayer2D.new ()
MOAISim.pushRenderPass ( layer )

viewport = MOAIViewport.new ()
viewport:setSize ( 640, 640 )
viewport:setScale ( 640, 640 )
layer:setViewport ( viewport )

tileDeck = MOAITileDeck2D.new ()
tileDeck:setTexture ( "iso-grid.png" )
tileDeck:setSize ( 8, 8 )
tileDeck:setRect ( -0.5, 0.5, 0.5, -0.5 )

grid = MOAIGrid.new ()
grid:setSize ( 20, 20, 32, 32 )

grid:setRow ( 1, 	0x01, 0x02, 0x03, 0x04, 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04 )
grid:setRow ( 2, 	0x09, 0x0a, 0x1a, 0x1a, 0x1a, 0x1a, 0x0b, 0x0c, 0x01, 0x02, 0x1a, 0x1a, 0x1a, 0x1a, 0x03, 0x04, 0x09, 0x0a, 0x0b, 0x0c )
grid:setRow ( 3, 	0x19, 0x19, 0x09, 0x0a, 0x0b, 0x0c, 0x1b, 0x1b, 0x09, 0x0a, 0x0b, 0x0c, 0x09, 0x0a, 0x0b, 0x0c, 0x19, 0x19, 0x1b, 0x1b )
grid:setRow ( 4, 	0x19, 0x19, 0x19, 0x19, 0x1b, 0x1b, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x1b )
grid:setRow ( 5, 	0x19, 0x19, 0x19, 0x19, 0x1b, 0x1b, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x1b )
grid:setRow ( 6, 	0x11, 0x12, 0x19, 0x19, 0x1b, 0x1b, 0x13, 0x14, 0x19, 0x19, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x1b, 0x11, 0x12, 0x13, 0x14 )
grid:setRow ( 7, 	0x00, 0x00, 0x11, 0x12, 0x13, 0x14, 0x00, 0x00, 0x11, 0x12, 0x13, 0x14, 0x11, 0x12, 0x13, 0x14, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 8, 	0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x01, 0x02, 0x03, 0x04, 0x00, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 9, 	0x09, 0x0a, 0x03, 0x04, 0x01, 0x02, 0x0b, 0x0c, 0x05, 0x0b, 0x0c, 0x09, 0x0a, 0x06, 0x19, 0x1b, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 10, 	0x19, 0x19, 0x09, 0x0a, 0x0b, 0x0c, 0x1b, 0x1b, 0x19, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x19, 0x1b, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 11, 	0x19, 0x19, 0x19, 0x19, 0x1b, 0x1b, 0x1b, 0x1b, 0x19, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x19, 0x1b, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 12, 	0x19, 0x19, 0x19, 0x19, 0x1b, 0x1b, 0x1b, 0x1b, 0x19, 0x1b, 0x1b, 0x19, 0x19, 0x1b, 0x12, 0x13, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 13, 	0x11, 0x12, 0x19, 0x19, 0x1b, 0x1b, 0x13, 0x14, 0x12, 0x13, 0x14, 0x11, 0x12, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 14, 	0x1c, 0x00, 0x11, 0x12, 0x13, 0x14, 0x00, 0x1c, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x0d, 0x0e, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 15, 	0x09, 0x07, 0x04, 0x00, 0x00, 0x01, 0x08, 0x0c, 0x0d, 0x08, 0x0c, 0x09, 0x07, 0x0e, 0x15, 0x16, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 16, 	0x19, 0x19, 0x09, 0x07, 0x08, 0x0c, 0x1b, 0x1b, 0x15, 0x1b, 0x1b, 0x19, 0x19, 0x16, 0x15, 0x16, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 17, 	0x19, 0x19, 0x19, 0x19, 0x1b, 0x1b, 0x1b, 0x1b, 0x15, 0x1b, 0x1b, 0x19, 0x19, 0x16, 0x15, 0x16, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 18, 	0x19, 0x19, 0x19, 0x19, 0x1b, 0x1b, 0x1b, 0x1b, 0x15, 0x1b, 0x1b, 0x19, 0x19, 0x16, 0x1d, 0x1e, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 19, 	0x11, 0x12, 0x19, 0x19, 0x1b, 0x1b, 0x13, 0x14, 0x1d, 0x13, 0x14, 0x11, 0x12, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 )
grid:setRow ( 20, 	0x00, 0x00, 0x11, 0x12, 0x13, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 )

prop = MOAIProp2D.new ()
prop:setDeck ( tileDeck )
prop:setGrid ( grid )
prop:setLoc ( -320, 320 )
prop:setScl ( 1, -1 )
layer:insertProp ( prop )
