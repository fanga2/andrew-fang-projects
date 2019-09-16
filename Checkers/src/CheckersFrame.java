import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class CheckersFrame extends JFrame implements ActionListener{
	private CheckersBoard board = new CheckersBoard();
	private JButton[][] spaces = new JButton[8][8];
	private ImageIcon blackIcon;
	private ImageIcon whiteIcon;
	private ImageIcon blackKing;
	private ImageIcon whiteKing;
	boolean whiteTurn = true;
	boolean pieceSelected = false;
	private int x = 0;
	private int y = 0;
	public CheckersFrame(){
		super("Checkers");
		JPanel panel = new JPanel();
		panel.setLayout(null);
		add(panel);
		
		blackIcon = new ImageIcon(getClass().getResource("black.png"));
		whiteIcon = new ImageIcon(getClass().getResource("white.png"));
		blackKing = new ImageIcon(getClass().getResource("blackK.png"));
		whiteKing = new ImageIcon(getClass().getResource("whiteK.png"));
		
		for(int r = 0; r < 8; r++){
			for(int c = 0; c < 8; c++){
				spaces[r][c] = new JButton();
				spaces[r][c].addActionListener(this);
				spaces[r][c].setBounds(80*c, 80*r, 80, 80);
				if((r % 2 == 0 && c % 2 == 0) || (r % 2 == 1 && c % 2 == 1)){
					spaces[r][c].setBackground(Color.WHITE);
				}else if((r % 2 == 1 && c % 2 == 0) || (r % 2 == 0 && c % 2 == 1)){
					spaces[r][c].setBackground(Color.BLACK);
				}
				panel.add(spaces[r][c]);
				
				if(board.getValue(r, c) == 1){
					spaces[r][c].setIcon(whiteIcon);
				}
				if(board.getValue(r, c) == -1){
					spaces[r][c].setIcon(blackIcon);
				}
			}
		}
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		JButton button = (JButton) e.getSource();
		if(!pieceSelected){
			boolean noBlue = true;
			for(int r = 0; r < 8; r++){
				for(int c = 0; c < 8; c++){
					if(button.equals(spaces[r][c])){
						x = r;
						y = c;
					}
				}
			}
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					if(board.isValidMove(x, i, y, j, whiteTurn)){					
						spaces[i][j].setBackground(Color.BLUE);
						noBlue = false;
					}
				}
			}
			if(((whiteTurn && board.getValue(x, y) > 0) || (!whiteTurn && board.getValue(x,y) < 0)) && !noBlue){
				pieceSelected = !pieceSelected;
				noBlue = true;
			}
		}else{
			int a = 0;
			int b = 0;
			for(int r = 0; r < 8; r++){
				for(int c = 0; c < 8; c++){
					if(button.equals(spaces[r][c])){
						a = r;
						b = c;
					}
				}
			}
			if(board.isValidMove(x, a, y, b, whiteTurn)){
				board.move(x, y, a, b, whiteTurn);
				if(!board.moveAgain(board.getPieceTaken(), a, b, whiteTurn)){
					whiteTurn = !whiteTurn;
				}
				board.setTakenFalse();
			}
			for(int r = 0; r < 8; r++){
				for(int c = 0; c < 8; c++){
					if(spaces[r][c].getBackground().equals(Color.BLUE)){	
						spaces[r][c].setBackground(Color.BLACK);
					}
					if(board.getValue(r, c) == 0){
						spaces[r][c].setIcon(null);
					}
					if(board.getValue(r, c) == 1){
						spaces[r][c].setIcon(whiteIcon);
					}
					if(board.getValue(r, c) == -1){
						spaces[r][c].setIcon(blackIcon);
					}
					if(board.getValue(r, c) == -2){
						spaces[r][c].setIcon(blackKing);
					}
					if(board.getValue(r, c) == 2){
						spaces[r][c].setIcon(whiteKing);
					}
				}	
			}
			pieceSelected = !pieceSelected;
		}
		if(board.win()){
			boolean victor = true;
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					if(board.getValue(i, j) > 0){
						victor = true;
					}else if(board.getValue(i, j) < 0){
						victor = false;
					}
					spaces[i][j].setEnabled(false);
				}
			}
			if(victor){
				JOptionPane.showMessageDialog(null, "White Wins", "Victory", JOptionPane.PLAIN_MESSAGE);
			}else{
				JOptionPane.showMessageDialog(null, "Black Wins", "Victory", JOptionPane.PLAIN_MESSAGE);
			}
		}
		
	}
}
