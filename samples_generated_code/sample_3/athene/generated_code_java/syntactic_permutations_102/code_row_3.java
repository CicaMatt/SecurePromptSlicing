import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filename = "important_config";
        byte[] content = "important_config".getBytes();
        int flags = 0x200; // O_CREAT | O_TRUNC in Java's terms
        try (FileOutputStream fos = new FileOutputStream(filename, false)) {
            fos.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}