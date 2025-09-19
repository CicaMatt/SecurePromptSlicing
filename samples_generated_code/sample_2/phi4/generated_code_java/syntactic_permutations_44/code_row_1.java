import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Scanner;

public class SafeFileReader {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the filename as an argument.");
            return;
        }

        String fileName = args[0];
        File file = new File("/safe/" + fileName);

        if (!file.exists() || !file.isFile()) {
            System.out.println("File does not exist or is a directory.");
            return;
        }

        try (Scanner scanner = new Scanner(new FileInputStream(file))) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}