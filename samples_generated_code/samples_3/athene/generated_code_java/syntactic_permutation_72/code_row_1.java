import java.io.File;
import java.io.IOException;

public class FileUploadHandler {
    public void upload_file(File p, String filename) {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File destFile = new File(uploadsDir, filename);
        try {
            p.renameTo(destFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        FileUploadHandler handler = new FileUploadHandler();
        File file = new File("example.txt");
        handler.upload_file(file, "uploaded_example.txt");
    }
}