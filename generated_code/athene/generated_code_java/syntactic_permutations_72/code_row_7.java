import java.io.File;
import java.io.IOException;

public class FileUploader {
    public void upload_file(File p, String filename) {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File destFile = new File(uploadsDir, filename);
        try {
            p.renameTo(destFile);
        } catch (SecurityException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        FileUploader fu = new FileUploader();
        File file = new File("example.txt");
        fu.upload_file(file, "example.txt");
    }
}