#!/usr/bin/tclsh

set WALL "#"
set BOX O
set SPOT +
set ON_SPOT 0
set SPACE " "
set PLAYER P
set INVALID "!"

set LAYOUT [list " " " " "#" "#" "#" "#" "#" " " "#" "#" "#" " " " " " " "#" " " "#" "+" " " "O" " " " " "#" " " "#" "#" "#" " " "O" "+" "#" " " "#" "+" "#" "#" "O" " " "#" " " "#" " " "#" " " "+" " " "#" "#" "#" "O" " " "0" "O" "O" "+" "#" "#" " " " " " " "+" " " " " "#" "#" "#" "#" "#" "#" "#" "#" "#"]

proc checkWin { level } {
	global ON_SPOT

	set spot0 [lindex $level 17]
	set spot1 [lindex $level 29]
	set spot2 [lindex $level 33]
	set spot3 [lindex $level 44]
	set spot4 [lindex $level 51]
	set spot5 [lindex $level 54]
	set spot6 [lindex $level 60]

	# Check if all boxes are on an spot
	if {
		$spot0 == $ON_SPOT &&
		$spot1 == $ON_SPOT &&
		$spot2 == $ON_SPOT &&
		$spot3 == $ON_SPOT &&
		$spot4 == $ON_SPOT &&
		$spot5 == $ON_SPOT &&
		$spot6 == $ON_SPOT
	} {
		puts "You won! Type restart to restart."
	}
}

proc render {level posX posY} {
	global PLAYER

	for {set i 0} {$i < 9} {incr i} {
		for {set j 0}  {$j < 8} {incr j} {
			set index [expr $i * 8 + $j]
			if {$i == $posY && $j == $posX} {
				puts -nonewline $PLAYER
			} else {
				puts -nonewline [lindex $level $index]
			}
		}
		puts ""
	}

	checkWin $level
}

proc getBlock {level x y} {
	global INVALID

	if {$x < 0 || $y < 0 || $x >= 8 || $y >= 9} {
		return $INVALID
	}

	set index [expr $y * 8 + $x]
	return [lindex $level $index]
}

proc updateLevel {level x y c} {
	set index [expr $y * 8 + $x]
	lset level $index $c
	return $level
}

proc movePlayer {level playerX playerY deltaX deltaY} {
	global WALL
	global BOX
	global SPOT
	global ON_SPOT
	global SPACE
	global INVALID

	set x [expr $playerX + $deltaX]
	set y [expr $playerY + $deltaY]

	set block [getBlock $level $x $y]

	if {$block == $INVALID || $block == $WALL} {
		# Can't move player
		return -code 1 $level
	}

	# Check if player is trying to push a block
	if {$block == $BOX || $block == $ON_SPOT} {
		set nextX [expr $x + $deltaX]
		set nextY [expr $y + $deltaY]

		set nextBlock [getBlock $level $nextX $nextY]

		# Check if can push block over
		if {$nextBlock == $SPACE || $nextBlock == $SPOT} {
			set oldBlock $SPOT
			set newBlock $ON_SPOT

			if {$block == $BOX } {
				set oldBlock $SPACE
			}

			if {$nextBlock == $SPACE} {
				set newBlock $BOX
			}

			set level [updateLevel $level $x $y $oldBlock ]
			set level [updateLevel $level $nextX $nextY $newBlock ]
		} else {
			# Can't move player
			return -code 1 $level
		}
	}

	return -code 0 $level
}

proc start {} {
	global LAYOUT
	set level $LAYOUT
	set position(x) 2
	set position(y) 2

	puts "Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.\n"

	while {1} {
		render $level $position(x) $position(y)
		puts ""
		puts Action: 
		gets stdin inputStr
		
		if {$inputStr == "exit" || $inputStr == "leave"} {
			break
		}

		if {$inputStr == "restart" || $inputStr == "reset"} {
			set level $LAYOUT
			set position(x) 2
			set position(y) 2
			continue
		}

		set strLen [ string length $inputStr ]

		for {set i 0} {$i < $strLen} {incr i} {
			set c [ string index $inputStr $i ]
			set code [catch {
				switch $c {
					"w" {
						set level [movePlayer $level $position(x) $position(y) 0 -1]
						set position(y) [expr $position(y) - 1 ]
					}
					"a" {
						set level [movePlayer $level $position(x) $position(y) -1 0]
						set position(x) [expr $position(x) - 1 ]
					}
					"s" {
						set level [movePlayer $level $position(x) $position(y) 0 1]
						set position(y) [expr $position(y) + 1 ]
					}
					"d" {
						set level [movePlayer $level $position(x) $position(y) 1 0]
						set position(x) [expr $position(x) + 1 ]
					}
				}
			} newLevel]
		}
	}
}

start