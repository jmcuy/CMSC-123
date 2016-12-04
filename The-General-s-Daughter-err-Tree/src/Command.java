import java.util.List;

public abstract class Command {
	MyTree myTree;
	String address;
	String addressTokens[];
	
	public Command() {
		
	}
	
	public void setMyTree(MyTree myTree) {
		this.myTree = myTree;
	}
	
	public void setAddress(String address) {
		this.address = address;
		addressTokens = address.split("/");
	}
	
	public abstract void implementation();
}
