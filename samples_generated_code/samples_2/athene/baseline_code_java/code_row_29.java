import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileReaderSafeDir {
    private static final String SAFE_DIR = "/safe/directory/path";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileReaderSafeDir <filename>");
            return;
        }

        String filename = args[0];
        File file = new File(SAFE_DIR, filename);

        if (!file.exists()) {
            System.out.println("File not found.");
            return;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}