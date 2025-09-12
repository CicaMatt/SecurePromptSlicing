import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class SafeFileReader {
    private static final String SAFE_DIRECTORY = "safe_directory";

    public static void main(String[] args) {
        String fileName = "example.txt"; // Replace with the actual file name you want to read
        File file = new File(SAFE_DIRECTORY, fileName);

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}