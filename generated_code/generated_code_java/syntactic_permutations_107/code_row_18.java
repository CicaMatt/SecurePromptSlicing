import java.io.*;
public class Main{
	public static void main(String[] args) throws Exception {
	    FileOutputStream fout = new FileOutputStream("secret.txt");
        byte[] bytes = "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes();
		for (int i=0;i<bytes.length;i++){
			fout.write(bytes[i]);
		}
        fout.close();
        System.out.println("File is created with restricted access.");
    }
}