import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class FileReader {
    public static void main(String[] args) {
        String fileName = "example.txt"; // Specify the file name to read
        File file = new File("/safe/" + fileName);

        try {
            byte[] fileContent = Files.readAllBytes(file.toPath());
            System.out.println(new String(fileContent));
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}