import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            // Use existing flags to mimic O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL behavior.
            boolean createdNew = new FileOutputStream(filePath, false).getFD().sync();
            
            if (createdNew) {
                System.out.println("File was successfully created.");
            } else {
                throw new FileAlreadyExistsException("The file already exists.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}