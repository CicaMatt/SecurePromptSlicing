import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFileFromSafeDirectory {

    public static void main(String[] args) {
        String filePath = "/safe/file.txt"; // Replace with your actual file path

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