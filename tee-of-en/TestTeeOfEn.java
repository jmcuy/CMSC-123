import java.io.*;

public class TestTeeOfEn {
	public static void main(String args[]) throws IOException {
		TeeOfEn sample1 = new TeeOfEn("inputFile.txt");
		System.out.println(sample1.answer());
	}
}