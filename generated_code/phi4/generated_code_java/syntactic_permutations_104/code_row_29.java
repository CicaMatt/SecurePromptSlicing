import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "example.txt";
        String contentToWrite = "important_config";

        try (FileOutputStream fileOut = new FileOutputStream(fileName, true)) {
            // Write the string important_config to the file
            fileOut.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}