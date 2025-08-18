import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            // Open or create the file for writing only, with specified flags behavior
            boolean success = openFile(filePath);
            
            if (success) {
                System.out.println("File opened/created successfully.");
                
                // Write some data to the file
                writeToFile(filePath, "Hello, World!");
            } else {
                System.err.println("Failed to open/create the file. It may already exist.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static boolean openFile(String filePath) throws IOException {
        File file = new File(filePath);

        // O_CREAT equivalent: Create a new file if it does not exist
        if (!file.exists()) {
            boolean created = file.createNewFile();

            // O_EXCL behavior: If file creation fails because the file already exists,
            // return false as if O_EXCL flag was set.
            if (!created) {
                throw new IOException("File already exists and cannot be overwritten.");
            }
        } else {
            // Truncate existing file to 0 bytes (O_TRUNC equivalent)
            boolean truncated = new FileOutputStream(file, false).close();
            
            if (!truncated) {
                throw new IOException("Failed to truncate the file.");
            }
        }

        return true;
    }

    private static void writeToFile(String filePath, String data) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(new File(filePath))) {
            fos.write(data.getBytes());
        }
    }
}