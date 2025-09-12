import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try {
            // Create the file if it doesn't exist
            File file = new File(fileName);
            boolean created = file.createNewFile();

            if (created || file.exists()) {
                // Open FileOutputStream with append mode and create new file if not exists
                try (FileOutputStream fos = new FileOutputStream(file, true)) {
                    fos.write(contentToWrite.getBytes());
                }
            } else {
                System.out.println("Failed to create the file.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}