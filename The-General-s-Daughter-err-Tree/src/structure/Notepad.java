package structure;
import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;

/**
 *	Text editor for creating files
 */
public class Notepad extends JFrame {
	public static final int OVERWRITE = 0;
	public static final int APPEND = 1;

	public MainSimulationGui directoryFrame;
	public JPanel contentPane;
	public JTextArea textArea;
	public MyNode file;
	public String fileName;
	public int instruction;
	public boolean fileExists;

	/**
	 * Create the frame.
	 */
	public Notepad(MainSimulationGui directoryFrame) {
		this.directoryFrame = directoryFrame;
		
		//*************************************
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		//-------------------------------------
		textArea = new JTextArea();
		textArea.setLineWrap(true);
		contentPane.add(textArea, BorderLayout.CENTER);
		//-------------------------------------		
		JScrollPane scrollPane = new JScrollPane(textArea);
		contentPane.add(scrollPane, BorderLayout.CENTER);
		//-------------------------------------
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				
				String contents = textArea.getText();
				FileDescriptor newFile;
				if(fileExists) {
					newFile = file.fileDescriptor;
					newFile.setContents(contents);
				} else {
					newFile = new FileDescriptor("file", fileName);
					newFile.setContents(contents);
					directoryFrame.myTree.insert(newFile);
				}
		
				directoryFrame.txtrAsd.setEditable(true);
				setVisible(false);
				
				// console output
				System.out.println(directoryFrame.fileSystem.showTree());
			}
		});
		//*************************************
	}
}
