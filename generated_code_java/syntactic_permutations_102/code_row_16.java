import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FileOutputStream fs = new FileOutputStream("important_config", true);
        String content = "important_config";
        byte[] buffer = content.getBytes();
        fs.write(buffer, 0, buffer.length);
    }
}