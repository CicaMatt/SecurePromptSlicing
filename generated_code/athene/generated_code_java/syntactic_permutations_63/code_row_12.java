import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileContentReader {
    public static void main(String[] args) {
        String filePath = "example.txt";
        StringBuilder contentBuilder = new StringBuilder();

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String currentLine;
            while ((currentLine = br.readLine()) != null) {
                contentBuilder.append(currentLine).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        String fileContent = contentBuilder.toString();
        System.out.println("File Content:\n" + fileContent);
    }
}