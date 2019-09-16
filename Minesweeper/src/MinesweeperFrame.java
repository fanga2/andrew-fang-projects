import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;
public class MinesweeperFrame extends JFrame implements MouseListener, ActionListener {
	private JButton[][] buttons;
	private int[][] values;
	private JLabel mineCounterLB;
	private int mineCounter;
	private JButton reset;
	private boolean pressed;
	private Random random;
	private boolean firstWin;
	private Icon mineIcon;
	private Icon flagIcon;
	public MinesweeperFrame(){
		super("Minesweeper");
		JPanel panel = new JPanel();
		panel.setLayout(null);
		add(panel);
		
		buttons = new JButton[8][8];
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				buttons[i][j] = new JButton();
				buttons[i][j].setBounds(j*50, i*50, 50, 50);
				buttons[i][j].addMouseListener(this);
				buttons[i][j].addActionListener(this);
				panel.add(buttons[i][j]);
			}
		}
		
		random = new Random();
		values = new int[8][8];
		int k = 0;
		while(k < 10){
			int column = random.nextInt(8);
			int row = random.nextInt(8);
			if(values[column][row] != -1){
				values[column][row] = -1;
				for(int l = -1; l <= 1; l++){
					for(int m = -1; m <= 1; m++){
						try{
							if(values[column+l][row+m] != -1){
								values[column+l][row+m]++;
							}
						}catch(Exception e){
							continue;
						}
					}
				}
				k++;
			}
			
		}
		
		mineCounter = 10; 
		mineCounterLB = new JLabel("Mines: " + mineCounter);
		mineCounterLB.setBounds(0, 420, 212, 10);
		panel.add(mineCounterLB);
		
		reset = new JButton("Reset");
		reset.setBounds(250, 405, 150, 55);
		reset.addActionListener(this);
		reset.setActionCommand("reset");
		panel.add(reset);
		
		firstWin = true;
		flagIcon = new ImageIcon(getClass().getResource("Picture2.png"));
		mineIcon = new ImageIcon(getClass().getResource("Picture1.png"));
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {}

    public void mousePressed(MouseEvent e) {
    	JButton button = (JButton) e.getSource();
        button.getModel().setArmed(true);
        button.getModel().setPressed(true);
        pressed = true;
    }

    @Override
    public void mouseReleased(MouseEvent e) {
    	JButton button = (JButton) e.getSource();
        button.getModel().setArmed(false);
        button.getModel().setPressed(false);
        if(pressed){
            if (SwingUtilities.isRightMouseButton(e) && firstWin) {
                if(button.getIcon() == null && button.isEnabled() && mineCounter > 0){
            		button.setIcon(flagIcon);
            		mineCounter--;
                }else if(button.getIcon() == flagIcon){
                	button.setIcon(null);
                	mineCounter++;
                }
                mineCounterLB.setText("Mines: " + mineCounter);
            }
        }
        pressed = false;

    }

    @Override
    public void mouseExited(MouseEvent e) {}

    @Override
    public void mouseEntered(MouseEvent e) {}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		JButton button = (JButton) e.getSource();
		if(e.getActionCommand().equals("reset")){
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					buttons[i][j].setIcon(null);
					buttons[i][j].setText("");
					buttons[i][j].setEnabled(true);
					values[i][j] = 0;
				}
			}
			int k = 0;
			while(k < 10){
				int column = random.nextInt(8);
				int row = random.nextInt(8);
				if(values[column][row] != -1){
					values[column][row] = -1;
					for(int l = -1; l <= 1; l++){
						for(int m = -1; m <= 1; m++){
							try{
								if(values[column+l][row+m] != -1){
									values[column+l][row+m]++;
								}
							}catch(Exception ex){
								continue;
							}
						}
					}
					k++;
				}
			}
			firstWin = true;
			mineCounter = 10;
			mineCounterLB.setText("Mines: " + mineCounter);
		}
		
		int x = -1;
		int y = -1;
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(button.equals(buttons[i][j])){
					x=i;
					y=j;
				}
			}
		}
		if(x > -1 && y > -1){
			checkButton(x, y, true);
		}
	}
	
    public void checkButton(int x, int y, boolean firstButton){
    	if(values[x][y] == -1 && firstButton){
    		for(int i = 0; i < 8; i++){
    			for(int j = 0; j < 8; j++){
    				buttons[i][j].setEnabled(false);
    				if(values[i][j] == -1){
    					buttons[i][j].setIcon(mineIcon);
    				}
    			}
    		}
    		JOptionPane.showMessageDialog(null, "You Lose! Better Luck Next Time", "You Lose!", JOptionPane.PLAIN_MESSAGE);
    	}else if(values[x][y] == 0){
    		buttons[x][y].setEnabled(false);
    		for(int i = -1; i <= 1; i++){
    			for(int j = -1; j <= 1; j++){
    				try{
    					if(values[x+i][y+j] != -1 && buttons[x+i][y+j].isEnabled()){	
    						try{
    							checkButton(x+i, y+j, false);
    						}catch(Exception e){
    							continue;
    						}
    					}	
    				}catch(Exception e){
    					continue;
    				}
    			}
    		}
    	}else if(values[x][y] > 0){
    		buttons[x][y].setText(Integer.toString(values[x][y]));
    		buttons[x][y].setEnabled(false);
    	}
    	
    	boolean win = true;
    	for(int i = 0; i < 8; i++){
    		for(int j = 0; j < 8; j++){
    			if((values[i][j] != -1 && (buttons[i][j].getIcon() == flagIcon || buttons[i][j].isEnabled())) || values[x][y] == -1){
    				win = false;
    				break;
    			}
    		}
    	}
    	if(win && firstWin){
    		for(int i = 0; i < 8; i++){
    			for(int j = 0; j < 8; j++){
    				if(values[i][j] == -1){
    					buttons[i][j].setIcon(flagIcon);
    				}
    				buttons[i][j].setEnabled(false);
    				mineCounter = 0;
    				mineCounterLB.setText("Mines: " + mineCounter);
    			}
    		}
    		firstWin = false;
    		JOptionPane.showMessageDialog(null, "You Win! Congragulations", "You Win!", JOptionPane.PLAIN_MESSAGE);
    	}
    }
}
