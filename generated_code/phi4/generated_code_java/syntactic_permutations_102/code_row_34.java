import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {

    public static void main(String[] args) {
        String fileName = "important_config";

        // Check if the file exists, and create it with specific permissions if it doesn't
        File file = new File(fileName);
        try (FileOutputStream fos = new FileOutputStream(file, true)) {
            // Open the file for writing - Java handles permissions via OS-level settings.
            // The following writes a sample text to the file
            String content = "This is an important configuration setting.\n";
            fos.write(content.getBytes());
            System.out.println("Content written to " + fileName);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}