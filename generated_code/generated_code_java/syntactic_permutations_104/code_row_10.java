import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FileOutputStream outputStream = new FileOutputStream("filename", true);
        String str = "important_config";
        byte buf[] = str.getBytes();
        outputStream.write(buf, 0, buf.length);
    }
}