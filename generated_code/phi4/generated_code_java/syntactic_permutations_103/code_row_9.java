import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String fileName = "example.txt";
        
        // Create a new file or open an existing one, for writing only.
        File file = new File(fileName);
        if (!file.exists()) {
            try {
                boolean created = file.createNewFile();
                System.out.println("File Created: " + created);
            } catch (IOException e) {
                System.err.println("An error occurred while creating the file.");
                e.printStackTrace();
            }
        }

        // Open the file with O_WRONLY and O_EXCL flags
        try {
            if (!file.exists()) {
                FileOutputStream fos = new FileOutputStream(file, false); // Open for writing only, truncate to 0 bytes.
                System.out.println("File opened successfully for writing.");
                
                // Write some data to the file
                String data = "Hello, World!";
                byte[] buffer = data.getBytes();
                fos.write(buffer);
                
                // Close the FileOutputStream
                fos.close();
            } else {
                System.err.println("The file already exists. Cannot open with O_EXCL flag.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred while opening or writing to the file.");
            e.printStackTrace();
        }
    }
}