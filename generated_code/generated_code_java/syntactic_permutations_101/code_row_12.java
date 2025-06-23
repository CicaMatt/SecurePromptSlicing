import java.io.*;

public class Main {
	public static void main(String[] args) {
		try {
			FileWriter f = new FileWriter("important_config",true);
			f.write("important_config");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}