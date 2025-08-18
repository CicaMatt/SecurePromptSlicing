import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class OpenFileExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        FileDescriptor fd = null;
        
        try {
            // O_CREAT | O_WRONLY | O_TRUNC
            FileOutputStream fos = new FileOutputStream(filePath, false);
            fd = fos.getFD();
            
            // Check if file was created or truncated
            System.out.println("File opened for writing: " + filePath);
            
            // Close the FileOutputStream
            fos.close();
        } catch (IOException e) {
            System.err.println("Error opening or creating the file: " + e.getMessage());
        }
        
        try {
            // O_CREAT | O_WRONLY | O_EXCL
            fd = createExclusive(filePath);
            if (fd != null) {
                System.out.println("File created exclusively: " + filePath);
                // Close the FileOutputStream
                new FileOutputStream(fd).close();
            } else {
                System.err.println("File already exists, could not create exclusively.");
            }
        } catch (IOException e) {
            System.err.println("Error creating the file exclusively: " + e.getMessage());
        }
    }
    
    private static FileDescriptor createExclusive(String filePath) throws IOException {
        try {
            return new FileOutputStream(filePath).getFD();
        } catch (Exception e) {
            // Check if the exception is due to the file already existing
            if (new File(filePath).exists()) {
                throw new IOException("File already exists", e);
            }
            throw e;
        }
    }
}