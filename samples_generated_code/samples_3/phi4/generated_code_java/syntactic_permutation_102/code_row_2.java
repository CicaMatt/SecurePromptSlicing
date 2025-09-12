import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "important_config";

        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            // Write some data to the file
            file.writeUTF("Sample configuration data.");
            
            // Optionally read from the file
            file.seek(0);  // Go back to the beginning of the file
            String content = file.readUTF();
            System.out.println("File content: " + content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}