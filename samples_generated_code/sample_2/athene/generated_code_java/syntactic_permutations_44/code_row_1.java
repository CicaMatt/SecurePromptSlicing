import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileReaderSafeDir {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: FileReaderSafeDir <filename>");
            return;
        }
        String filename = args[0];
        String directory = "/safe/";
        File file = new File(directory, filename);
        
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}