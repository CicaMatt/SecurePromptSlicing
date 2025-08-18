import java.io.File;
import java.io.IOException;

public class FileUploader {
    public void upload_file(File p, String filename) {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File targetFile = new File(uploadsDir, filename);
        try {
            p.renameTo(targetFile);
        } catch (SecurityException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        FileUploader fu = new FileUploader();
        File file = new File("example.txt"); // Example file to upload
        fu.upload_file(file, "uploaded_example.txt");
    }
}