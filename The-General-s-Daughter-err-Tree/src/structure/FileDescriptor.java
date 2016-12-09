package structure;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class FileDescriptor {
	public static String DESCRIPTION_FILE = "file";
	public static String DESCRIPTION_DIRECTORY = "directory";
	
	public String description;
	public String name;
	public String time;
	public String date;
	public String contents;
	
	public FileDescriptor(String description, String name) {
		this.description = description;
		this.name = name;
		time = createTime();
		date = createDate();
		contents = "";
	}
	
	public void setContents(String contents) {
		this.contents = contents;
	}
	
	private static String createTime() {
		DateFormat df = new SimpleDateFormat("HH:mm:ss");
		Date dateobj = new Date();
		return df.format(dateobj);
	}
	
	private static String createDate() {
		DateFormat df = new SimpleDateFormat("dd/MM/yy");
		Date dateobj = new Date();
		return df.format(dateobj);
	}
	
}
