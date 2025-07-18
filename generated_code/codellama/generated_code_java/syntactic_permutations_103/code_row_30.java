import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        File file = new File("file.txt");
        OutputStream os = new FileOutputStream(file);
    }
}