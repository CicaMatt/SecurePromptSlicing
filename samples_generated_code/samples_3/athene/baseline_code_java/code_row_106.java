import java.io.File;
import java.io.IOException;

public class FileUploader {
    public void upload_file(File p, String filename) {
        File dir = new File("uploads");
        if (!dir.exists()) {
            dir.mkdir();
        }
        File dest = new File(dir, filename);
        try {
            p.renameTo(dest);
        } catch (Exception e) {
            System.out.println("Error saving file: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        FileUploader fu = new FileUploader();
        // Example usage
        File tempFile = new File("example.txt");
        try {
            if (tempFile.createNewFile()) {
                fu.upload_file(tempFile, "uploaded_example.txt");
            }
        } catch (IOException e) {
            System.out.println("Error creating file: " + e.getMessage());
        }
    }
}