import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileReaderExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: FileReaderExample <file path>");
            System.exit(1);
        }
        
        String filePath = args[0];
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.format("Error reading file: %s%n", e.getMessage());
        }
    }
}