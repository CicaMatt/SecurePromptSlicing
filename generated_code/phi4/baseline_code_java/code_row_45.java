import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReaderFromSafeDirectory {

    public static void main(String[] args) {
        String filePath = "safe_directory/example.txt"; // Change this to your specific file path

        File file = new File(filePath);

        if (file.exists() && !file.isDirectory()) {
            try (FileInputStream fis = new FileInputStream(file)) {
                int content;
                while ((content = fis.read()) != -1) {
                    System.out.print((char) content);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("File does not exist or is a directory.");
        }
    }
}
