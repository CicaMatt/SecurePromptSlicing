import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    private static final String SAFE_DIRECTORY = "safe_directory/";

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a file name as an argument.");
            return;
        }

        String fileName = args[0];
        readFile(SAFE_DIRECTORY + fileName);
    }

    private static void readFile(String filePath) {
        try (FileInputStream fis = new FileInputStream(new File(filePath))) {
            int content;
            while ((content = fis.read()) != -1) {
                System.out.print((char) content);
            }
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }
}