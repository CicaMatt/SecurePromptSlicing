import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    private static final String SAFE_DIRECTORY = "path/to/safe/directory";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: FileReader <filename>");
            return;
        }

        String filename = args[0];
        readFile(SAFE_DIRECTORY, filename);
    }

    private static void readFile(String directoryPath, String fileName) {
        File file = new File(directoryPath + File.separator + fileName);

        if (!file.exists() || !file.isFile()) {
            System.out.println("File does not exist or is not a regular file.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            int content;
            while ((content = fis.read()) != -1) {
                // Process the byte 'content' as needed
                System.out.print((char) content);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}


Replace `"path/to/safe/directory"` with the actual path to your safe directory.