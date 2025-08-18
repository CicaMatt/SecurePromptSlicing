import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class SafeFileReader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = "/safe/" + args[0];
        
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}