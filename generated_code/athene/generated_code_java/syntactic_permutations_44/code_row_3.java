import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileReaderUtility {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: FileReaderUtility <filename>");
            System.exit(1);
        }
        String filename = "/safe/" + args[0];
        readFileContents(filename);
    }

    private static void readFileContents(String filePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}