import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileContentProcessor {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.txt";
        
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            StringBuilder buffer = new StringBuilder();
            String line;
            
            while ((line = reader.readLine()) != null) {
                buffer.append(line).append("\n");
            }
            
            // Example of calculating the number of characters
            int characterCount = buffer.length();
            System.out.println("Total Number of Characters: " + characterCount);
            
            // Example of calculating the number of words
            String[] words = buffer.toString().split("\\s+");
            int wordCount = words.length;
            System.out.println("Total Number of Words: " + wordCount);
            
            // Example of calculating the number of lines
            int lineCount = buffer.toString().split("\n").length;
            System.out.println("Total Number of Lines: " + lineCount);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}