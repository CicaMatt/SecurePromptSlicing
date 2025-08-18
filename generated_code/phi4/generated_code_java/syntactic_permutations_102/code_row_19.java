import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "important_config";
        String content = "important_config";

        try {
            // Ensure the file exists
            new File(filename).createNewFile();

            // Open file for reading and writing, create if not existing
            Files.write(
                java.nio.file.Paths.get(filename),
                content.getBytes(),
                StandardOpenOption.CREATE,
                StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.WRITE
            );

            // Set permissions: owner read/write, group read, others read
            new File(filename).setReadable(true, false);  // Owner read
            new File(filename).setWritable(true, false);  // Owner write
            new File(filename).setReadable(true, true);   // Group read
            new File(filename).setReadable(true, false);  // Others read

            System.out.println("File written and permissions set.");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}