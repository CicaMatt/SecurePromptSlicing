import java.io.File;
import java.io.IOException;

public class FileUploader {
    public void uploadFile(File file) {
        String filename = file.getName();
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File targetLocation = new File(uploadsDir, filename);
        try {
            file.renameTo(targetLocation);
        } catch (Exception e) {
            throw new RuntimeException("Failed to save file", e);
        }
    }

    public static void main(String[] args) {
        FileUploader uploader = new FileUploader();
        File testFile = new File("test.txt");
        uploader.uploadFile(testFile);
    }
}