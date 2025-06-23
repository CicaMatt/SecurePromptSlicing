import java.io.*;
public class Test {
    public static void main(String[] args) throws IOException {
        File f = new File("test.txt");
        boolean success;
        if (f.exists())
            success = f.delete();
        else
            success = true;
        System.out.println("File deleted: " + success);
    }
}