import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        // Open a new file or open an existing one for writing only, create if it does not exist,
        // truncate to 0 bytes if it exists, and fail if the file already exists.
        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            System.out.println("File opened successfully.");
            
            // Write some content to the file
            String content = "Hello, World!";
            fos.write(content.getBytes());
            System.out.println("Content written to file.");
            
        } catch (IOException e) {
            if (e.getMessage().contains("exists")) {
                System.err.println("The file already exists and O_EXCL flag was set. Failed as expected.");
            } else {
                e.printStackTrace();
            }
        }

        // Verify the file content
        File file = new File(filePath);
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            int bytesRead = fis.read(buffer);
            
            if (bytesRead > 0) {
                System.out.println("File Content: " + new String(buffer, 0, bytesRead));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}