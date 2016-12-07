import java.util.ArrayList;
import java.util.List;

public class MyNode {
	FileDescriptor fileDescriptor;
	MyNode parent;
	List<MyNode> children;
	
	public MyNode(FileDescriptor fileDescriptor) {
		this.fileDescriptor = fileDescriptor;
		children = new ArrayList<MyNode>();
		parent = null;
	}
	
	public String toString(int level) {
		String stringResult = "";
		
		for(int i = 0; i < level; i++) {
			stringResult += "   ";
		}
		stringResult += fileDescriptor.name;
		stringResult += "\n";
		
		for(MyNode childNode : children) {
			stringResult += childNode.toString(level + 1);
		}
		
		return stringResult;
	}
}
