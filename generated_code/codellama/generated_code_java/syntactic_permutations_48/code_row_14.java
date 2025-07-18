package main;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URLDecoder;

public class img {
	public static void main(String[] args) throws FileNotFoundException, IOException {
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Enter the file name");
		String filename = br.readLine();
		File myfile = new File(filename);
		if (!myfile.exists()) {
			throw new IOException("Unable to find the file");
		} else {
			BufferedReader in = new BufferedReader(new FileReader(myfile));
			String str;
			while ((str=in.readLine())!=null) {
				System.out.println(str);
			}
			in.close();
		}
	}
}