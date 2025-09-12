import java.io.File;
import java.io.IOException;

public class FileUploader {
    public void uploadFile(File p) {
        String filename = p.getName();
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File dest = new File(uploadsDir, filename);
        try {
            p.renameTo(dest);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        FileUploader uploader = new FileUploader();
        File file = new File("example.txt");
        uploader.uploadFile(file);
    }
}