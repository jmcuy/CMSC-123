
public class FileSystem {
	MyTree myTree;
	CommandMaker commandMaker;
	
	public FileSystem(MyTree myTree) {
		this.myTree = myTree;
		commandMaker = new CommandMaker();
	}
	
	public void implementation(String command, String address) {
		commandMaker.implementation(myTree, command, address);
	}
}
