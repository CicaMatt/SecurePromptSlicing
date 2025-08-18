import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            // Equivalent to O_CREAT | O_TRUNC | O_WRONLY | O_EXCL in POSIX systems
            FileOutputStream fos = new FileOutputStream(new File(filePath), false);
            
            if (fos.getChannel().size() == 0) { 
                System.out.println("File created or truncated successfully.");
                
                // Write data to the file
                String data = "Hello, World!";
                byte[] bytes = data.getBytes();
                fos.write(bytes);
                
                System.out.println("Data written to file: " + data);
            } else {
                System.out.println("File already exists and is not empty. Exiting...");
                fos.close();
            }
            
        } catch (IOException e) {
            if (e.getMessage().contains("exists")) {
                System.out.println("File creation failed because the file already exists.");
            } else {
                e.printStackTrace();
            }
        }
    }
}