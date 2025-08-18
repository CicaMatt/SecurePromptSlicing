import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "example.txt";

        try {
            // Create or open the file with flags equivalent to O_CREAT | O_WRONLY | O_TRUNC | O_EXCL
            if (createFile(fileName)) {
                System.out.println("File created successfully.");
            } else {
                System.out.println("File already exists, could not create a new one.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static boolean createFile(String fileName) throws IOException {
        File file = new File(fileName);
        
        // O_CREAT | O_EXCL: Create the file if it does not exist; fail if it already exists.
        if (!file.createNewFile()) {
            return false;
        }
        
        // O_WRONLY | O_TRUNC: Open for writing only and truncate to zero length.
        try (FileOutputStream fos = new FileOutputStream(file, false)) {
            // File is opened with truncation to 0 bytes
        }

        return true;
    }
}