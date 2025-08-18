import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filename = "important_config.txt";
        String content = "important_config";

        try {
            openAndWriteFile(filename, content);
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static void openAndWriteFile(String filename, String content) throws IOException {
        File file = new File(filename);

        try (FileOutputStream fos = new FileOutputStream(file, false)) {
            fos.write(content.getBytes());
        }
    }
}