import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            openOrCreateFile(filePath);
        } catch (IOException e) {
            System.err.println("Error occurred: " + e.getMessage());
        }
    }

    private static void openOrCreateFile(String fileName) throws IOException {
        Path path = Paths.get(fileName);

        // Equivalent of O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
        if (!Files.exists(path)) {
            Files.createFile(path);
        } else {
            throw new IOException("File already exists");
        }

        try (var fileChannel = FileChannel.open(
                path,
                StandardOpenOption.WRITE,
                StandardOpenOption.TRUNCATE_EXISTING)) {

            // Perform write operations here
            ByteBuffer buffer = ByteBuffer.allocate(1024);
            buffer.put("Hello, World!".getBytes());
            buffer.flip();
            fileChannel.write(buffer);

        } catch (IOException e) {
            throw new IOException("Failed to open or truncate the file", e);
        }
    }
}