
public class CheckersBoard {
	int[][] board = new int[8][8];
	private boolean pieceTaken = false;
	public CheckersBoard(){
		for(int r = 0; r < 8; r++){
			for(int c = 0; c < 8; c++){
				board[r][c] = 0;
			}
		}
		boolean odds = true;
		for(int r = 0; r < 3; r++){
			for(int c = 0; c < 8; c++){
				if((c % 2 == 1 && odds) || (!odds && c % 2 == 0)){
					board[r][c] = -1;
				}
			}
			odds = !odds;
		}
		odds = false;
		for(int r = 5; r < 8; r++){
			for(int c = 0; c < 8; c++){
				if((c % 2 == 1 && odds) || (!odds && c % 2 == 0)){
					board[r][c] = 1;
				}
			}
			odds = !odds;
		}
	}
	public void move(int startR, int startC, int endR, int endC, boolean whiteTurn){
		if(isValidMove(startR, endR, startC, endC, whiteTurn)){
			if(forcedTake(startR, startC, whiteTurn)){
				if(endR < startR && endC < startC){
					board[startR-1][startC-1] = 0;
				}
				if(endR < startR && endC > startC){
					board[startR-1][startC+1] = 0;
				}
				if(endR > startR && endC < startC){
					board[startR+1][startC-1] = 0;
				}
				if(endR > startR && endC > startC){
					board[startR+1][startC+1] = 0;
				}
				pieceTaken = true;
			}
			board[endR][endC] = board[startR][startC];
			board[startR][startC] = 0;
			for(int c = 0; c < 8; c++){
				if(board[0][c] == 1){
					board[0][c] = 2;
				}
				if(board[7][c] == -1){
					board[7][c] = -2;
				}
			}
		}
	}
	public boolean isValidMove(int r1, int r2, int c1, int c2, boolean whiteTurn){		
		if(board[r2][c2] != 0){
			return false;
		}
		if(board[r1][c1] != 0){	
			if(c2 >= 0 && c2 < 8 && r2 >= 0 && c2 < 8 && c1 >= 0 && c1 < 8 && r1 >= 0 && c1 < 8){			
				if(forcedTakeAvailable(whiteTurn) && !forcedTake(r1, c1, whiteTurn)){
					return false;
				}
				if(!forcedTake(r1, c1, whiteTurn)){
					return regularCheck(r1, r2, c1, c2, whiteTurn);
				}else if(forcedTake(r1, c1, whiteTurn)){	
					return forcedCheck(r1, r2, c1, c2, whiteTurn);
				}
			}
		}
		return false;
	}
	public boolean forcedTake(int r, int c, boolean whiteTurn){
		if(whiteTurn){	
			try{
			 	if(board[r-1][c+1] < 0 && board[r-2][c+2] == 0){return true;}
			}catch(Exception e){}
			try{
				if(board[r-1][c-1] < 0 && board[r-2][c-2] == 0){return true;}
			}catch(Exception e){}	
			if(board[r][c] == 2){
				try{
					if(board[r+1][c+1] < 0 && board[r+2][c+2] == 0){return true;}
				}catch(Exception e){}
				try{
					if(board[r+1][c-1] < 0 && board[r+2][c-2] == 0){return true;}
				}catch(Exception e){}
			}
		}else{
			try{
			 	if(board[r+1][c+1] > 0 && board[r+2][c+2] == 0){return true;}
			}catch(Exception e){}
			try{
				if(board[r+1][c-1] > 0 && board[r+2][c-2] == 0){return true;}
			}catch(Exception e){}	
			if(board[r][c] == -2){
				try{
					if(board[r-1][c+1] > 0 && board[r-2][c+2] == 0){return true;}
				}catch(Exception e){}
				try{
					if(board[r-1][c-1] > 0 && board[r-2][c-2] == 0){return true;}
				}catch(Exception e){}
			}
		}
		return false;
	}
	public int getValue(int r, int c){
		return board[r][c];
	}
	public boolean moveAgain(boolean tookPiece, int r, int c, boolean whiteTurn){
		if(tookPiece && forcedTake(r,c, whiteTurn)){
			return true;
		}
		return false;
	}
	public boolean win(){
		boolean blackPresent = false;
		boolean whitePresent = false;
		for(int i = 0 ; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(board[i][j] < 0){
					blackPresent = true;
				}
				if(board[i][j] > 0){
					whitePresent = true;
				}
			}
		}
		return !(blackPresent && whitePresent);
	}
	public boolean regularCheck(int r1, int r2, int c1, int c2, boolean whiteTurn){
		if(whiteTurn && board[r1][c1] > 0){
			for(int i = -1; i <= 1; i+=2){
				try{
					if(r2 == r1 - 1  && c2 == c1 + i){
						return true;
					}
				}catch(Exception e){}
				try{
					if(board[r1][c1] == 2 && r2 == r1+1 && c2 == c1+i){
						return true;
					}					
				}catch(Exception e){}
			}
		}else if(!whiteTurn && board[r1][c1] < 0){
			for(int i = -1; i <= 1; i+=2){
				try{
					if(r2 == r1 + 1  && c2 == c1 + i){
						return true;
					}
				}catch(Exception e){}
				try{
					if(board[r1][c1] == -2 && r2 == r1-1 && c2 == c1+i){
						return true;
					}					
				}catch(Exception e){}
			}
		}
		return false;
	}
	public boolean forcedCheck(int r1, int r2, int c1, int c2, boolean whiteTurn){
		for(int j = -1; j <= 1; j+=2){
			if(whiteTurn && board[r1][c1] > 0){
				try{
					if(r1-2 == r2 && c1+(2*j) == c2 && board[r1-1][c1+j] < 0){						
						return true;
					}								
				}catch(Exception e){}
				try{
					if(board[r1][c1] == 2 && r1+2 == r2 && c1+(2*j) == c2 && board[r1+1][c1+j] < 0){
						return true;
					}
				}catch(Exception e){}
			}else if(!whiteTurn && board[r1][c1] < 0){
				try{
					if(board[r1+1][c1+j] > 0 && r1+2 == r2 && c1+(2*j) == c2){
						return true;
					}
				}catch(Exception e){}
				try{
					if(board[r1][c1] == -2 && r1-2 == r2 && c1+(2*j) == c2 && board[r1-1][c1+j] > 0){
						return true;
					}
				}catch(Exception e){}
			}	
		}
		return false;
	}
	public boolean forcedTakeAvailable(boolean whiteTurn){
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(whiteTurn){
					if(forcedTake(i, j, true) && board[i][j] > 0){
						return true;
					}
				}else{
					if(forcedTake(i, j, false) && board[i][j] < 0){
						return true;
					}
				}
			}
		}
		return false;
	}
	public boolean getPieceTaken(){
		return pieceTaken;
	}
	public void setTakenFalse(){
		pieceTaken = false;
	}
}
