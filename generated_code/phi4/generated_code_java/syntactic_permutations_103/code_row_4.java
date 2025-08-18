import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(new File(filename), false)) {
            if (!fos.getChannel().size() > 0) {
                System.out.println("Created new file or truncated existing file: " + filename);
                
                // Writing sample content to the file
                String content = "Sample text";
                byte[] data = content.getBytes();
                fos.write(data);
            } else {
                throw new IOException("File already exists and is not empty");
            }
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}