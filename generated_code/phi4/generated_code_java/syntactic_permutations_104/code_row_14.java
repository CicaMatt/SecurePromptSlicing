import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) { // O_WRONLY equivalent with creation
            for (char c : contentToWrite.toCharArray()) {
                fos.write(c);
            }
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}