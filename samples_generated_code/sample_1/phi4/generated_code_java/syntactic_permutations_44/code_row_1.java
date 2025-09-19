import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class SafeFileReader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java SafeFileReader <filename>");
            System.exit(1);
        }

        String fileName = args[0];
        File file = new File("/safe/" + fileName);

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}