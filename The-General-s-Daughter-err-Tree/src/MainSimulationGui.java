import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.KeyStroke;
import javax.swing.border.EmptyBorder;

public class MainSimulationGui extends JFrame {
	private static final String key = "ENTER";

	private JPanel contentPane;
	private JTextArea txtrAsd;
	private String typeValue;
	private KeyStroke keyStroke;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		MyTree myTree = new MyTree();
		FileSystem fileSystem = new FileSystem(myTree);
		
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainSimulationGui frame = new MainSimulationGui(myTree);
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
		
	}
	
    private Action wrapper = new AbstractAction() {
        @Override
        public void actionPerformed(ActionEvent ae) {
        	System.out.println(txtrAsd.getText());
            txtrAsd.append("\n");
        }
    };

	/**
	 * Create the frame.
	 */
	public MainSimulationGui(MyTree myTree) {

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		
		txtrAsd = new JTextArea();
		txtrAsd.setText(myTree.currentAbsolutePath() + ">");
		
		/**Key Binding**/
		txtrAsd.setLineWrap(true);
		keyStroke = KeyStroke.getKeyStroke(key);
		Object actionKey = txtrAsd.getInputMap(JComponent.WHEN_FOCUSED).get(keyStroke);
		txtrAsd.getActionMap().put(actionKey, wrapper);
		/***************/
		
		contentPane.add(txtrAsd, BorderLayout.CENTER);
		
		JScrollPane scrollPane = new JScrollPane(txtrAsd);
		contentPane.add(scrollPane);
	}

}
