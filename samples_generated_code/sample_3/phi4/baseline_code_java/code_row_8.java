import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileReaderFromSafeDirectory {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java FileReaderFromSafeDirectory <filename>");
            return;
        }

        String filename = args[0];
        String safeDirPath = "/path/to/safe/directory"; // Replace with the actual path of your safe directory

        File fileToRead = new File(safeDirPath, filename);

        if (!fileToRead.exists() || !fileToRead.isFile()) {
            System.err.println("File does not exist or is not a regular file.");
            return;
        }

        try {
            String content = new String(Files.readAllBytes(fileToRead.toPath()));
            System.out.println("Content of the file:");
            System.out.println(content);
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}
