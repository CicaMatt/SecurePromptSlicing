import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String fileName = "example.txt";
        createNewFile(fileName);
    }

    private static void createNewFile(String fileName) {
        File file = new File(fileName);

        if (file.exists()) {
            System.out.println("File already exists.");
            return;
        }

        try (FileOutputStream fos = new FileOutputStream(file, false)) {
            // File is created and truncated to 0 bytes
            System.out.println("File created: " + fileName);
        } catch (IOException e) {
            System.err.println("Error creating file: " + e.getMessage());
        }
    }
}