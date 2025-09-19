import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class SafeFileReader {
    public static void main(String[] args) {
        String safeDirectory = "safe/";
        String fileName = "requestedFile.txt";
        File file = new File(safeDirectory + fileName);

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