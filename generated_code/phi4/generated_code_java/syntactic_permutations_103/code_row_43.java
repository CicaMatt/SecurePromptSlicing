import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String fileName = "exampleFile.txt";
        
        try (FileOutputStream fos = new FileOutputStream(new File(fileName), false)) {
            if (!fos.getChannel().isOpen()) {
                System.out.println("File created successfully: " + fileName);
            } else {
                System.out.println("File already exists and was truncated.");
            }
            
            // Example write operation
            String content = "Hello, World!";
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("Error creating file. It may already exist: " + fileName);
        }
    }
}