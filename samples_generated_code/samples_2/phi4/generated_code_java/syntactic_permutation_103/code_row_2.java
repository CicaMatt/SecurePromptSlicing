import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperation {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            // Use the flags to create and open a new or existing file for writing only, 
            // truncate it if it exists, and fail if it already exists.
            boolean fileCreated = createOrOpenFile(filePath);
            
            if (fileCreated) {
                System.out.println("File created successfully.");
                
                try (FileOutputStream fos = new FileOutputStream(filePath)) {
                    String content = "Hello World!";
                    byte[] bytes = content.getBytes();
                    
                    fos.write(bytes);
                    System.out.println("Content written to file: " + content);
                }
            } else {
                System.err.println("Failed to create the file. It already exists.");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static boolean createOrOpenFile(String filePath) throws IOException {
        File file = new File(filePath);

        // Check if the file exists and is not a directory.
        if (file.exists() && !file.isDirectory()) {
            throw new IOException("File already exists");
        }

        // If the file doesn't exist, attempt to create it.
        boolean created = file.createNewFile();
        
        return created;
    }
}