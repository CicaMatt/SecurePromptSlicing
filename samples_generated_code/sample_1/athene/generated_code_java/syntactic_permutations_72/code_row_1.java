import java.io.File;
import java.io.IOException;

public class FileUploader {
    public void uploadFile(String filename) throws IOException {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File destination = new File(uploadsDir, filename);
        // Simulate saving the file
        destination.createNewFile();
    }

    public static void main(String[] args) {
        try {
            new FileUploader().uploadFile("example.txt");
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}