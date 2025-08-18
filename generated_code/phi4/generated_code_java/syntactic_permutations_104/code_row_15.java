import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String dataToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) { // Open for reading and writing, create if not exists
            fos.write(dataToWrite.getBytes());
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}