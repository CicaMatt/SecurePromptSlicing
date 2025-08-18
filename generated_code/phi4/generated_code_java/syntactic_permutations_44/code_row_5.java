import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class SafeFileReader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = args[0];
        File file = new File("/safe/" + filename);

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            int bytesRead = fis.read(data);
            
            if (bytesRead == -1) {
                System.out.println("Error reading the file.");
                return;
            }

            String content = new String(data, 0, bytesRead, StandardCharsets.UTF_8);
            System.out.println(content);

        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}