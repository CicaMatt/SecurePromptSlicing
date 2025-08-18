import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class SafeFileReader {
    private static final String SAFE_DIRECTORY = "/path/to/safe/directory/";

    public static void main(String[] args) {
        String fileName = "example.txt";
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