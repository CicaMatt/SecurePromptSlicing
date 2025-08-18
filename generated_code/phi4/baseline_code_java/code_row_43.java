import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class SafeFileReader {
    public static void main(String[] args) {
        String filePath = "/safe/somefile.txt"; // Specify your file name here
        File file = new File(filePath);

        if (!file.exists()) {
            System.out.println("The file does not exist.");
            return;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}