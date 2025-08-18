import java.io.File;
import java.io.IOException;

public class FileUploader {
    public static void main(String[] args) {
        upload_file("example.txt");
    }

    public static void upload_file(String filename) {
        FileuploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        
        File fileToSave = new File(uploadsDir, filename);
        try {
            fileToSave.createNewFile(); // Simulate saving the file
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}