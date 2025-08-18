import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileSafeReader {
    private static final String SAFE_DIRECTORY = "/path/to/safe/directory/";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileSafeReader <filename>");
            return;
        }

        String filename = args[0];
        File file = new File(SAFE_DIRECTORY + filename);

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}