import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileReader {
    public static void main(String[] args) {
        String filePath = "/safe/somefile.txt"; // Change this to your actual file path

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