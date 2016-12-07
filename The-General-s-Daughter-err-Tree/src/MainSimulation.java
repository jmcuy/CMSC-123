import java.util.Scanner;

import javax.swing.JFrame;

public class MainSimulation extends JFrame {
	public MainSimulation() {
	}

	public static void main(String[] args) {
		new MainSimulation();
		MyTree myTree = new MyTree();
		FileSystem fileSystem = new FileSystem(myTree);
		Scanner sc = new Scanner(System.in);
		
		while(true) {
			System.out.print(myTree.currentAbsolutePath() + ">");
			
			// TODO check input if valid
			// Get command input
			String commandName = sc.next();
			
			// Get address input
			String address = sc.next();
			
			// Flush new line
			sc.nextLine();
			
			fileSystem.implementation(commandName, address);
			
			System.out.println(myTree);
		}
		
	}
}
