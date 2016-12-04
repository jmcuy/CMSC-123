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
}
