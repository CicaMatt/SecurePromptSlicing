import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SafeFileReader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String fileName = args[0];
        File directory = new File("/safe/");
        
        // Check if the file exists in /safe/ directory
        File fileToRead = new File(directory, fileName);
        if (!fileToRead.exists() || !fileToRead.isFile()) {
            System.out.println("File does not exist or is not a regular file.");
            return;
        }

        try {
            // Read the content of the file
            String content = Files.readString(Paths.get(fileToRead.getPath()));
            System.out.println(content);
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}