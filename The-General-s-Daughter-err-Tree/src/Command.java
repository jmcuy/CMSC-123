import java.util.List;

public abstract class Command {
	
	public Command() {
		
	}
	
	
	/*
	 	String addressTokens[] = address.split("/");
		
		if(addressTokens[0].equals("")) {
			// absolute path implementation
		} else {
			// relative path implementation
			myTree.traversor = myTree.access;
		}
	 */
	public abstract void implementation(MyTree myTree, String address);

}
