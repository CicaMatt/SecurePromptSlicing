import java.io.*;

public class FileOperations {
	public static void main(String[] args) throws IOException {
		FileWriter fw = new FileWriter("secret.txt");
        BufferedWriter bf = new BufferedWriter(fw);
        bf.write("Hello, World!");
        bf.close();
        fw.close();
        
        Runtime.getRuntime().exec("chmod 040 secret.txt");
	}
}