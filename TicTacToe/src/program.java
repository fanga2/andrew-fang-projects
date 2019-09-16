import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class program extends JFrame implements ActionListener {
	private JButton topleft;
	private JButton topmiddle;
	private JButton topright;
	private JButton centerleft;
	private JButton centermiddle;
	private JButton centerright;
	private JButton bottomleft;
	private JButton bottommiddle;
	private JButton bottomright;
	private JButton reset;
	private int turn = 1;
	private int oCount = 0;
	private int xCount = 0;
	private int tieCount = 0;
	private JLabel xDisplay;
	private JLabel oDisplay;
	private JLabel tieDisplay;
	
	public program(){
		super("TicTacToe");
		JPanel panel = new JPanel();
		panel.setLayout(null);
		add(panel);
		topleft = new JButton();	
		topleft.addActionListener(this);
		topleft.setActionCommand("click1");
		topleft.setBounds(0, 0, 120, 120);
		panel.add(topleft);
		
		topmiddle = new JButton();
		topmiddle.addActionListener(this);
		topmiddle.setActionCommand("click2");
		topmiddle.setBounds(250, 0, 120, 120);
		panel.add(topmiddle);
		
		topright = new JButton();
		topright.addActionListener(this);
		topright.setActionCommand("click3");
		topright.setBounds(500, 0, 120, 120);
		panel.add(topright);
		
		centerleft = new JButton();
		centerleft.addActionListener(this);
		centerleft.setActionCommand("click4");
		centerleft.setBounds(0, 250, 120, 120);
		panel.add(centerleft);
		
		centermiddle = new JButton();
		centermiddle.addActionListener(this);
		centermiddle.setActionCommand("click5");
		centermiddle.setBounds(250, 250, 120, 120);
		panel.add(centermiddle);
		
		centerright = new JButton();
		centerright.addActionListener(this);
		centerright.setActionCommand("click6");
		centerright.setBounds(500, 250, 120, 120);
		panel.add(centerright);
		
		bottomleft = new JButton();
		bottomleft.addActionListener(this);
		bottomleft.setActionCommand("click7");
		bottomleft.setBounds(0, 500, 120, 120);
		panel.add(bottomleft);
		
		bottommiddle = new JButton();
		bottommiddle.addActionListener(this);
		bottommiddle.setActionCommand("click8");
		bottommiddle.setBounds(250, 500, 120, 120);
		panel.add(bottommiddle);
		
		bottomright = new JButton();
		bottomright.addActionListener(this);
		bottomright.setActionCommand("click9");
		bottomright.setBounds(500, 500, 120, 120);
		panel.add(bottomright);
		
		reset = new JButton("Reset");
		reset.addActionListener(this);
		reset.setActionCommand("resetgame");
		reset.setBounds(750, 250, 120, 120);
		panel.add(reset);
		
		xDisplay = new JLabel("X Wins: " + xCount);
		xDisplay.setBounds(750,100, 120, 120);
		panel.add(xDisplay);
		
		oDisplay = new JLabel("O Wins: " + oCount);
		oDisplay.setBounds(750, 120, 120, 120);
		panel.add(oDisplay);
		
		tieDisplay = new JLabel("Ties: " + tieCount);
		tieDisplay.setBounds(750, 140, 120, 120);
		panel.add(tieDisplay);
	}

	
	public void actionPerformed(ActionEvent e) {
		String action = e.getActionCommand();
		turn++;
		if (turn%2 == 0 && turn != 1){
			if (action.equals("click1")){
				topleft.setText("X");
				topleft.setEnabled(false);
			}else if (action.equals("click2")){
				topmiddle.setText("X");
				topmiddle.setEnabled(false);
			}else if (action.equals("click3")){
				topright.setText("X");
				topright.setEnabled(false);
			}else if (action.equals("click4")){
				centerleft.setText("X");
				centerleft.setEnabled(false);
			}else if (action.equals("click5")){
				centermiddle.setText("X");
				centermiddle.setEnabled(false);
			}else if (action.equals("click6")){
				centerright.setText("X");
				centerright.setEnabled(false);
			}else if (action.equals("click7")){
				bottomleft.setText("X");
				bottomleft.setEnabled(false);
			}else if (action.equals("click8")){
				bottommiddle.setText("X");
				bottommiddle.setEnabled(false);
			}else if (action.equals("click9")){
				bottomright.setText("X");
				bottomright.setEnabled(false);
			}
		}else if (turn%2 == 1 && turn != 10){
			if (action.equals("click1")){
				topleft.setText("O");
				topleft.setEnabled(false);
			}else if (action.equals("click2")){
				topmiddle.setText("O");
				topmiddle.setEnabled(false);
			}else if (action.equals("click3")){
				topright.setText("O");
				topright.setEnabled(false);
			}else if (action.equals("click4")){
				centerleft.setText("O");
				centerleft.setEnabled(false);
			}else if (action.equals("click5")){
				centermiddle.setText("O");
				centermiddle.setEnabled(false);
			}else if (action.equals("click6")){
				centerright.setText("O");
				centerright.setEnabled(false);
			}else if (action.equals("click7")){
				bottomleft.setText("O");
				bottomleft.setEnabled(false);
			}else if (action.equals("click8")){
				bottommiddle.setText("O");
				bottommiddle.setEnabled(false);
			}else if (action.equals("click9")){
				bottomright.setText("O");
				bottomright.setEnabled(false);
				}
		}
		
		String result1 = topleft.getText();
		String result2 = topmiddle.getText();
		String result3 = topright.getText();
		String result4 = centerleft.getText();
		String result5 = centermiddle.getText();
		String result6 = centerright.getText();
		String result7 = bottomleft.getText();
		String result8 = bottommiddle.getText();
		String result9 = bottomright.getText();

		if ((result1 == "X" && result5 == "X" && result9 == "X") && !action.equals("resetgame")
		|| (result3 == "X" && result5 == "X" && result7 == "X") && !action.equals("resetgame")
		|| (result1 == "X"&& result4 == "X" && result7 == "X") && !action.equals("resetgame")
		|| (result2 == "X" && result5 == "X" && result8== "X") && !action.equals("resetgame")
		|| (result3 == "X" && result6 == "X" && result9== "X") && !action.equals("resetgame")
		|| (result1 == "X" &&result2 == "X" && result3 == "X") && !action.equals("resetgame")
		|| (result4 == "X" && result5 == "X" && result6=="X") && !action.equals("resetgame")
		|| (result7 == "X" && result8 == "X" && result9 =="X") && !action.equals("resetgame")) {
			JOptionPane.showMessageDialog(null, "X Wins", "Result", JOptionPane.PLAIN_MESSAGE);
			turn = 1;
			xCount++;
			xDisplay.setText("X Wins: " + xCount);
			topleft.setEnabled(false);
			topmiddle.setEnabled(false);
			topright.setEnabled(false);
			centerleft.setEnabled(false);
			centermiddle.setEnabled(false);
			centerright.setEnabled(false);
			bottomleft.setEnabled(false);
			bottommiddle.setEnabled(false);
			bottomright.setEnabled(false);
		}else if ((result1 == "O" && result5 == "O" && result9 == "O") && !action.equals("resetgame") 
		|| (result3 == "O" && result5 == "O" && result7 == "O") && !action.equals("resetgame")
		|| (result1 == "O" && result4 == "O" && result7 == "O") && !action.equals("resetgame")
		|| (result2 == "O" && result5 == "O" && result8 == "O") && !action.equals("resetgame")
		|| (result3 == "O" && result6 == "O" && result9 == "O") && !action.equals("resetgame")
		|| (result1 == "O" && result2 == "O" && result3 == "O") && !action.equals("resetgame")
		|| (result4 == "O" && result5 == "O" && result6 == "O") && !action.equals("resetgame")
		|| (result7 == "O" && result8 == "O" && result9 == "O") && !action.equals("resetgame")){
			JOptionPane.showMessageDialog(null, "O wins", "Result", JOptionPane.PLAIN_MESSAGE);
			turn = 1;
			oCount++;
			oDisplay.setText("O Wins: " + oCount);
			topleft.setEnabled(false);
			topmiddle.setEnabled(false);
			topright.setEnabled(false);
			centerleft.setEnabled(false);
			centermiddle.setEnabled(false);
			centerright.setEnabled(false);
			bottomleft.setEnabled(false);
			bottommiddle.setEnabled(false);
			bottomright.setEnabled(false);
		}else if(turn == 10){
			JOptionPane.showMessageDialog(null, "The Result is a Tie", "Result", JOptionPane.PLAIN_MESSAGE);
			turn = 1;
			tieCount++;
			tieDisplay.setText("Ties: " + tieCount);
		}
		if (action.equals("resetgame")){
			topleft.setText(null);
			topleft.setEnabled(true);
			topmiddle.setText(null);
			topmiddle.setEnabled(true);
			topright.setText(null);
			topright.setEnabled(true);
			centerleft.setText(null);
			centerleft.setEnabled(true);
			centermiddle.setText(null);
			centermiddle.setEnabled(true);
			centerright.setText(null);
			centerright.setEnabled(true);
			bottomleft.setText(null);
			bottomleft.setEnabled(true);
			bottommiddle.setText(null);
			bottommiddle.setEnabled(true);
			bottomright.setText(null);
			bottomright.setEnabled(true);
			turn = 1;
		}
		
			
	
	
			
	
			}
		;
	};
	
	

