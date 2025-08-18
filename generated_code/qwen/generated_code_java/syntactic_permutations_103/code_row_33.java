import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpenExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean fileCreated = false;

        try {
            File file = new File(filePath);
            if (!file.exists()) {
                fileCreated = file.createNewFile();
            } else {
                FileOutputStream fos = new FileOutputStream(file, false); // O_TRUNC flag equivalent
                fos.close();
            }

            if (fileCreated) {
                System.out.println("File created: " + filePath);
            } else {
                System.out.println("File opened for writing: " + filePath);
            }
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }
}