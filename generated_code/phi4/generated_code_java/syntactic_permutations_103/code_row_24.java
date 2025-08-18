import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            // Equivalent of O_CREAT | O_TRUNC | O_WRONLY | O_EXCL in Java
            FileOutputStream fos = new FileOutputStream(new File(filePath), false);
            
            if (fos.getChannel().size() == 0) { // Check that the file is empty, meaning it was created.
                System.out.println("File created and opened for writing.");
            } else {
                fos.close();
                throw new IOException("File already exists");
            }

        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}