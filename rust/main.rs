use std::io::{stdin, stdout, Write};

type LevelType = [char; 72];

const W:i32 = 8;
const H:i32 = 9;
const W_U: usize = 8;

const WALL:char = '#';
const BOX:char = 'O';
const SPOT: char = '+';
const ON_SPOT: char = '0';
const SPACE: char = ' ';
const PLAYER: char = 'P';
const INVALID: char = '!';
const LAYOUT: LevelType = [' ', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', '#', '+', ' ', 'O', ' ', ' ', '#', ' ', '#', '#', '#', ' ', 'O', '+', '#', ' ', '#', '+', '#', '#', 'O', ' ', '#', ' ', '#', ' ', '#', ' ', '+', ' ', '#', '#', '#', 'O', ' ', '0', 'O', 'O', '+', '#', '#', ' ', ' ', ' ', '+', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#'];


fn main() {
	let mut level: LevelType = LAYOUT;
	let mut player = (2, 2);
	let mut input_str = String::new();

	println!("Type w,a,s,d to move. Can type multiple characters to move. Write reset to restart.");

	loop {
		render(level, player);
		check_win(&mut level);
		println!("");
		print!("Action: ");

		stdout().flush().unwrap();
		input_str.clear();
		
		let _ = stdin().read_line(&mut input_str);

		if input_str.contains("exit") {
			break;
		}

		if input_str.contains("reset") || input_str.contains("restart") {
			level = LAYOUT;
			player = (2, 2);
			continue;
		}

		for c in input_str.chars() { 
			match c {
				'w' => move_player(&mut player, &mut level, 0, -1),
				'a' => move_player(&mut player, &mut level, -1, 0),
				's' => move_player(&mut player, &mut level, 0, 1),
				'd' => move_player(&mut player, &mut level, 1, 0),
				_ => {}
			}
		}
	}

}

fn move_player(player:&mut (i32, i32), level: &mut LevelType, delta_x: i32, delta_y: i32) {
	let x:i32 = player.0 + delta_x;
	let y:i32 = player.1 + delta_y;

	let block = get_block(level, x, y);

	if block == INVALID || block == WALL {
		return;
	}

	if block == BOX || block == ON_SPOT {	
		// Check if user is trying to push a block
		let next_x = x + delta_x;
		let next_y = y + delta_y;
		
		let next_block = get_block(level, next_x, next_y);

		// Check if there space available behind the block
		if next_block == SPACE || next_block == SPOT {
			update_level(level, x, y, if block == BOX {SPACE} else {SPOT});
			update_level(level, next_x, next_y, if next_block == SPACE {BOX} else {ON_SPOT});
		} else {
			return;
		}
	}

	player.0 = x;
	player.1 = y;
}

fn update_level(level: &mut LevelType, x:i32, y:i32, block: char) {
	let index:usize = (y * W + x).try_into().unwrap();
	level[index] = block;
}

fn get_block(level: &mut LevelType, x:i32, y:i32) -> char {
	if x < 0 || y < 0 {
		return INVALID
	}
	
	if(x >= W) || (y >= H) {
		return INVALID;
	}

	let index:usize = (y * W + x).try_into().unwrap();

	return level[index];
}

fn render(arr: LevelType, player:(i32, i32)) {
	let player_index = player.1 * W + player.0;

	for i in 0..72 {
		if player_index as usize == i {
			print!("{}", PLAYER);
		} else {
			print!("{}", arr[i]);
		}

		if i % W_U == W_U-1 {
			println!();
		}
	}
}

fn check_win(level: &mut LevelType) {
	let won =  {
		level[2 * W_U + 1] == ON_SPOT &&
		level[3 * W_U + 5] == ON_SPOT &&
		level[4 * W_U + 1] == ON_SPOT &&
		level[5 * W_U + 4] == ON_SPOT &&
		level[6 * W_U + 3] == ON_SPOT &&
		level[6 * W_U + 6] == ON_SPOT &&
		level[7 * W_U + 4] == ON_SPOT
	};

	if won {
		println!("You won! Type restart to restart.")
	}
}