import java.io.*;

public class JavaSecret {
	public static void main(String[] args) throws IOException {
		String secret = "Super Secret Information";

		File file = new File("secretfile.txt");
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file)));
		bw.write(secret);
		bw.close();
		file.setReadable(true, true);

		System.out.println(file);
	}
}