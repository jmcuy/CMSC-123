package structure;
import java.awt.BorderLayout;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.KeyStroke;
import javax.swing.border.EmptyBorder;

import keybinds.ImplementCommand;
import keybinds.KeyBind;

/*********************************
 * TODO:
 * -other commands
 * -match output file
 * -serialization
 * -improvement of GUI
 *********************************/

public class MainSimulationGui extends JFrame {
	
	public MyTree myTree;
	public FileSystem fileSystem;
	public JPanel contentPane;
	public JTextArea txtrAsd;
	public KeyStroke keyStroke;
	public int startIndex;
	public Notepad notepad;
	private KeyBind implementCommand;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {		
		MainSimulationGui frame = new MainSimulationGui();
		frame.setVisible(true);
	}
	
	/**
	 * Creates the JFrame. Initializes components and other fields.
	 */
	public MainSimulationGui() {
		myTree = new MyTree();
		fileSystem = new FileSystem(this);
		notepad = new Notepad(this);
		notepad.setVisible(false);
		implementCommand = new ImplementCommand(this);
		
		/**Initialize MainSimulationGui JFrame Components**/
		//***************************************************
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		//---------------------------------------------------
		txtrAsd = new JTextArea();
		txtrAsd.setText(myTree.currentAbsolutePath() + ">");
		txtrAsd.setLineWrap(true);
		//---------------------------------------------------
		keyStroke = KeyStroke.getKeyStroke(implementCommand.getKey());
		Object actionKey = txtrAsd.getInputMap(JComponent.WHEN_FOCUSED).get(keyStroke);
		txtrAsd.getActionMap().put(actionKey, implementCommand);
		//---------------------------------------------------
		contentPane.add(txtrAsd, BorderLayout.CENTER);
		//---------------------------------------------------
		JScrollPane scrollPane = new JScrollPane(txtrAsd);
		contentPane.add(scrollPane);
		//***************************************************
		
		// initialize file start index
		startIndex = txtrAsd.getText().length();
	}
}
