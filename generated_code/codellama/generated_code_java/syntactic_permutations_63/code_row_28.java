import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class ReadFile {
	public static void main(String[] args) throws IOException {
		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader("file1.txt"));
			ArrayList<String> buffer = new ArrayList<String>();
			int checksum = 0;
			while (true) {
				String line = reader.readLine();
				if (line == null) break;
				buffer.add(line);
				for (int i=0;i<line.length();i++) {
					checksum += (int) line.charAt(i);
				}
			}
			if (checksum == 0) System.out.println("buffer is empty.");
			reader.close();
			String str = "";
			for (String s : buffer) {
				str += s + "\n";
			}
			FileWriter writer = new FileWriter("file2.txt");
			writer.write(Integer.toString(buffer.size()) + " " + Integer.toString(checksum) + "\n" + str);
			writer.close();
		} finally {
			if (reader != null) reader.close();
		}
	}
}