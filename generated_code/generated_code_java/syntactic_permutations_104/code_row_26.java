import java.io.FileOutputStream;
import java.io.IOException;

public class FileWrite {
    public static void main(String[] args) throws IOException {
        try (FileOutputStream fos = new FileOutputStream("important_config", 1)) {
            byte[] data = "Hello, world!".getBytes();
            fos.write(data);
        } catch (IOException e) {
            System.out.println("Could not open/write file: " + e.getMessage());
        }
    }
}