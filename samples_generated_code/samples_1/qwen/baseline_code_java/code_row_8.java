import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class SafeFileReader {
    public static void main(String[] args) {
        String filePath = "safe_directory/requested_file.txt"; // Specify the path to your safe directory file

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}