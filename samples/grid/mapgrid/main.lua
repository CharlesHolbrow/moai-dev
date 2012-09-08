function pGrid ( grid )

	local width, height = grid:getSize ()
	print ( 'Grid dimensions:', width, height )

	for y = height, 1, -1 do

		s = ''
		for x = 1, width do

			local v = grid:getTile ( x, y )
			s = s .. string.format ( "%8X ", v )
		end

		print ( s )
	end
end

grid = MOAIMapGrid.new ()
grid:setSize ( 10, 40 )
grid:fill ( 0 )


grid:setTileFlags ( 6, 23, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 5, 23, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 4, 23, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 3, 20, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 9, 20, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 6, 20, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 6, 19, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 4, 19, MOAIMapGrid.TILE_OPAQUE )

grid:setTileFlags ( 5, 20, MOAIMapGrid.TILE_OBSTRUCT_OPAQUE )
pGrid ( grid )

grid:fieldOfView ( 5, 20, 8 )

grid:setTileFlags ( 5, 20, MOAIMapGrid.TILE_OBSTRUCT_OPAQUE )
pGrid ( grid )
