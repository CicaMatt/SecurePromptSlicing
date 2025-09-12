import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class SafeFileReader {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = "/safe/" + args[0];
        File file = new File(filename);

        if (!file.exists() || !file.isFile()) {
            System.out.println("Error: File does not exist or is a directory.");
            return;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}