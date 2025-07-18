import java.io.*;

public class OpenFile {
    public static void main(String[] args) throws IOException {
        FileOutputStream f = new FileOutputStream("filename.txt", true); //creates file or opens it if already exists
        PrintWriter p = new PrintWriter(f);
        p.println("This is a test"); //writes data to file
        p.close(); //closes the file
    }
}