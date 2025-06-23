import java.io.FileOutputStream;
import java.io.IOException;

public class FileSystem {
    public static void main(String[] args) {
        try (FileOutputStream outputStream = new FileOutputStream("important_config", true)) {
            byte[] bytesToWrite = "important_config".getBytes();
            outputStream.write(bytesToWrite);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e);
        }
    }
}