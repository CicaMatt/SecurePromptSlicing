import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileSafeReader {
    private static final String SAFE_DIRECTORY = "safe/";

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java FileSafeReader <filename>");
            return;
        }

        String fileName = args[0];
        String filePath = SAFE_DIRECTORY + fileName;

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