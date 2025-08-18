import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            boolean fileCreated = createOrOpenFile(filePath);
            System.out.println("File created: " + fileCreated);

            // Additional operations can be performed here after ensuring the file is ready
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static boolean createOrOpenFile(String filePath) throws IOException {
        File file = new File(filePath);
        
        // Using O_CREAT to create if it doesn't exist and O_TRUNC to truncate if it exists.
        try (FileOutputStream fos = new FileOutputStream(file, false)) {
            return true;  // File is created/truncated successfully
        }
    }
}