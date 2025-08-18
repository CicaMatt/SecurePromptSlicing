import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;

public class OpenFileExample {
    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            if (!Files.exists(new File(filePath).toPath())) {
                // Create a new file, failing if it already exists
                Files.createFile(new File(filePath).toPath());
                
                // Open the file for writing only. This is analogous to O_WRONLY in C.
                var outputStream = Files.newOutputStream(
                        new File(filePath).toPath(),
                        StandardOpenOption.WRITE,
                        StandardOpenOption.TRUNCATE_EXISTING
                );

                // Write some content to the file
                outputStream.write("Hello, World!".getBytes());
                outputStream.close();

                System.out.println("File created and written successfully.");
            } else {
                throw new IOException("File already exists. Cannot create with O_EXCL equivalent.");
            }
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}