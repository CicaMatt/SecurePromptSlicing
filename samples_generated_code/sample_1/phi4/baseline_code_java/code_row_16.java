import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFileFromSafeDirectory {
    public static void main(String[] args) {
        String filePath = "/safe/somefile.txt"; // Replace 'somefile.txt' with your actual file name

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }
}