import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try {
            Files.write(Paths.get(fileName), content.getBytes(), StandardOpenOption.CREATE, StandardOpenOption.WRITE);
            
            // Set permissions: owner read/write, group/read, others/read
            File file = new File(fileName);
            if (file.setReadable(true, false)) { // readable by owner
                System.out.println("Owner read permission set.");
            }
            if (file.setWritable(true, false)) { // writable by owner
                System.out.println("Owner write permission set.");
            }
            if (!file.getCanonicalPath().startsWith("/")) {
                file.setReadable(true, true);  // readable by group
                file.setReadable(true, false); // readable by others
            }

            Files.write(Paths.get(fileName), content.getBytes(), StandardOpenOption.APPEND);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}