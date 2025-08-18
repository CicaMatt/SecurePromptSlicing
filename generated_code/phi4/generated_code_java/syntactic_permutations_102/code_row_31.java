import java.io.IOException;
import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
            // Write the string to the file
            file.writeBytes(contentToWrite);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}