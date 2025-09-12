import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFileFromSafeDirectory {

    public static void main(String[] args) {
        String filePath = "/safe/safefile.txt"; // Replace with your specific file name

        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}


Make sure to replace `/safe/safefile.txt` with the actual file path you intend to read from. Ensure that your application has the necessary permissions to access files in this directory.