import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FileOutputStream fileOutputStream = new FileOutputStream("important_file", true);
        fileOutputStream.write("important_config".getBytes());
        fileOutputStream.close();
    }
}