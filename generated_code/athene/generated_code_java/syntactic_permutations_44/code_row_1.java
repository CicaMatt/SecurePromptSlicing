import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: FileReader <filename>");
            System.exit(1);
        }
        String fileName = args[0];
        File file = new File("/safe/" + fileName);
        try (FileInputStream fis = new FileInputStream(file)) {
            int content;
            while ((content = fis.read()) != -1) {
                System.out.print((char) content);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}