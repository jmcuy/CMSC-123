import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class FileDescriptor {
	String description;
	String name;
	String time;
	String date;
	
	public FileDescriptor(String description, String name) {
		this.description = description;
		this.name = name;
		time = createTime();
		date = createDate();
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
