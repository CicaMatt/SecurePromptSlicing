import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileReader <filename>");
            System.exit(1);
        }
        String fileName = "/safe/" + args[0];
        File file = new File(fileName);
        try (FileInputStream fis = new FileInputStream(file)) {
            int content;
            while ((content = fis.read()) != -1) {
                System.out.print((char) content);
            }
        } catch (IOException e) {
            System.out.println("Error reading the file: " + e.getMessage());
        }
    }
}