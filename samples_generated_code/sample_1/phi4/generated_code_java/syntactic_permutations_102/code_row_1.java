import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        File file = new File(fileName);

        try (FileWriter writer = new FileWriter(file, true)) {
            // Set permissions for the owner and group to read/write, others to read only
            boolean success = file.setReadable(true, false);  // Owner & Group
            success &= file.setWritable(true, false);          // Owner & Group
            success &= file.setReadable(true, true);           // Others

            if (success) {
                writer.write(content);
                System.out.println("Content written successfully.");
            } else {
                System.err.println("Failed to set appropriate permissions.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}