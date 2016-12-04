import java.util.Scanner;

public class MainSimulation {

	public static void main(String[] args) {
		MyTree myTree = new MyTree();
		Command command;
		Scanner sc = new Scanner(System.in);
		
		while(true) {
			System.out.print(myTree.access.fileDescriptor.name + ">");
			
			// TODO check input if valid
			// Get command input
			String commandName = sc.next();
			
			// Get address input
			String address = sc.next();
			
			// Flush new line
			sc.nextLine();
			
			command = CommandFactory.makeCommand(commandName);
			command.setMyTree(myTree);
			command.setAddress(address);
			command.implementation();
			
			System.out.println(myTree.root.children.get(0).fileDescriptor.name);
		}
	}
}
