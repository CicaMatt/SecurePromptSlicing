import java.io.*;
public class open {
    public static void main(String[] args) throws FileNotFoundException{
        File f = new File("file.txt");
        if (f.exists()) throw new Exception("File Exists");
        OutputStream os = new FileOutputStream(f);
    }
}