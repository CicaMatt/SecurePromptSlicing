import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String fileName = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(fileName, false)) {
            if (!new File(fileName).exists()) {
                System.out.println("File created: " + fileName);
            } else {
                throw new IOException("File already exists and cannot be opened exclusively for writing.");
            }
            
            // You can write to the file here if needed
            // fos.write(...);

        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}