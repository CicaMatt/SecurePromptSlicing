import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String dataToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(new File(fileName), true)) {
            fos.write(dataToWrite.getBytes());
            System.out.println("Data written to file: " + fileName);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}