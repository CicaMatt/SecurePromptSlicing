import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        Path path = Paths.get(fileName);

        try {
            // O_CREAT | O_TRUNC | O_WRONLY
            Files.write(path, new byte[0], StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
            System.out.println("File opened or created and truncated for writing.");
            
            // To simulate O_EXCL, we need to check if the file exists before creating it.
            // Here's how you could do it separately:
            /*
            if (Files.exists(path)) {
                throw new IOException("File already exists.");
            } else {
                Files.createFile(path);
                System.out.println("File created exclusively for writing.");
            }
            */
        } catch (IOException e) {
            System.err.println("Error opening or creating the file: " + e.getMessage());
        }
    }
}