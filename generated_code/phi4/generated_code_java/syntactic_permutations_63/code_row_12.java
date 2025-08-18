import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileContentReader {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.txt"; // Update with your file path

        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(filePath));
            StringBuilder buffer = new StringBuilder();
            String line;
            
            while ((line = reader.readLine()) != null) {
                buffer.append(line).append("\n");
            }

            String content = buffer.toString();

            // Example calculation: Counting the number of characters
            int characterCount = content.length();

            System.out.println("Total Characters: " + characterCount);

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}