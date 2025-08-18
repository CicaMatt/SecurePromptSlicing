import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "important_config";

        try (RandomAccessFile file = new RandomAccessFile(filePath, "rw")) {
            // Write a sample string to the file
            file.writeUTF("Sample configuration data.");

            System.out.println("Data written successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}