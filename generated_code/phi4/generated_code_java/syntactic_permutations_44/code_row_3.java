import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SafeFileReader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = args[0];
        Path filePath = Paths.get("/safe/", filename);

        try {
            byte[] fileContent = Files.readAllBytes(filePath);
            System.out.println(new String(fileContent));
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}