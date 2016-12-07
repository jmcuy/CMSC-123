
public class CommandMaker {
	Command mkdir = new Mkdir();
	Command rmdir = new Rmdir();
	Command cd = new Cd();
	Command error = new Error();
	
	public void CommandMaker() {
		
	}
	
	public void implementation(MyTree myTree, String command, String address) {
		switch(command) {
		case "mkdir" : 
			mkdir.implementation(myTree, address);
			break;
		case "rmdir" :
			rmdir.implementation(myTree, address);
			break;
		case "cd" :
			cd.implementation(myTree, address);
			break;
		default : 
			error.implementation(myTree, address);
			break;
		}
	}
}
