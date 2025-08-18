import java.io.File;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "example.txt";
        
        try {
            // Attempt to create a new file, truncating it if it exists
            boolean createdOrTruncated = createFile(fileName);
            System.out.println("Create or truncate file: " + (createdOrTruncated ? "Success" : "Failed"));
            
            // Attempt to open an existing file for writing only and fail if it already exists
            boolean exclusiveOpen = exclusiveOpenForWrite(fileName);
            System.out.println("Exclusive open for write: " + (exclusiveOpen ? "Success" : "Failed"));
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }

    public static boolean createFile(String fileName) throws IOException {
        File file = new File(fileName);

        if (file.exists()) {
            file.delete();
        }

        return file.createNewFile();
    }

    public static boolean exclusiveOpenForWrite(String fileName) throws IOException {
        File file = new File(fileName);
        
        if (!file.exists() || !file.canWrite()) {
            // If the file doesn't exist or can't be written to, attempt creation
            if (createFile(fileName)) {
                return true;
            }
            return false;
        } else {
            return false; // File exists and is writable, so exclusive open fails
        }
    }
}