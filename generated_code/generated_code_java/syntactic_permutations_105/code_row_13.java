package com.mycompany.helloworld;
import java.io.*;

public class App {
	public static void main(String[] args) throws IOException {
		File f = new File("secret.txt");
		if (!f.exists()) {
			f.createNewFile();
		}
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(
				new FileOutputStream(f), "UTF-8"));
		String line = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
		bw.write(line + "\n");
		bw.close();
		f.setReadable(true, false); // readable by owner only
		f.setWritable(true, false); // writable by owner only
		f.setExecutable(false, true); // non-executable by others
	}
}