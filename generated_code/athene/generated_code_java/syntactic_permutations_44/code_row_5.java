import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileReaderSafeDir {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: FileReaderSafeDir <filename>");
            System.exit(1);
        }
        
        String fileName = "/safe/" + args[0];
        File file = new File(fileName);
        
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }
}