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
grid:fill ( 24 )


-- flat line overhead
grid:setTileFlags ( 6, 23, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 5, 23, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 4, 23, MOAIMapGrid.TILE_OPAQUE )
-- Should be obsturcted be the line
grid:setTileFlags ( 5, 24, MOAIMapGrid.TILE_OPAQUE )

-- parallel, two spaces to the left, and obsructed 4 spaces to left
grid:setTileFlags ( 7, 20, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 9, 20, MOAIMapGrid.TILE_OPAQUE )

-- Test a Corner
grid:setTileFlags ( 2, 20, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 2, 21, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 3, 21, MOAIMapGrid.TILE_OPAQUE )

-- Tiles directly below 5, 20
grid:setTileFlags ( 5, 19, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 5, 18, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 5, 17, MOAIMapGrid.TILE_OPAQUE )
grid:setTileFlags ( 5, 16, MOAIMapGrid.TILE_OPAQUE )



grid:setTileFlags ( 5, 20, MOAIMapGrid.TILE_OBSTRUCT_OPAQUE )
pGrid ( grid )

grid:fieldOfView ( 5, 20, 10 )

grid:setTileFlags ( 5, 20, MOAIMapGrid.TILE_OBSTRUCT_OPAQUE )
pGrid ( grid )
