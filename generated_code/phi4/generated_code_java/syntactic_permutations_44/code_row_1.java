import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class SafeFileReader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = args[0];
        File file = new File("/safe/" + filename);

        try (Scanner scanner = new Scanner(file)) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                System.out.println(line);
            }
        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + file.getAbsolutePath());
        }
    }
}