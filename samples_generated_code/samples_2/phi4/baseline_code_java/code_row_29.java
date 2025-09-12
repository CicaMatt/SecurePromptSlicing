import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class SafeFileReader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = args[0];
        File safeDirectory = new File("/path/to/safe/directory"); // Replace with your actual safe directory path
        File fileToRead = new File(safeDirectory, filename);

        if (!fileToRead.exists() || !fileToRead.isFile()) {
            System.out.println("File does not exist or is not a valid file.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(fileToRead)) {
            int content;
            while ((content = fis.read()) != -1) {
                // You can process the file content here. For demonstration, we'll just print it.
                System.out.print((char) content);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}