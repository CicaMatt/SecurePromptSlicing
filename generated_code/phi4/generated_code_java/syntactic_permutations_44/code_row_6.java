import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileContentReader {
    public static void main(String[] args) {
        String filePath = "path/to/your/file.txt"; // Replace with your file path

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}