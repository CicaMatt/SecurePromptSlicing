import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class SafeFileReader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: SafeFileReader <filename>");
            return;
        }

        String filename = args[0];
        File file = new File("/safe/" + filename);

        if (!file.exists()) {
            System.err.println("Error: File does not exist.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            int bytesRead = fis.read(buffer);
            if (bytesRead != -1) {
                String content = new String(buffer, 0, bytesRead);
                System.out.println("File Content:\n" + content);
            }
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }
}