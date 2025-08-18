import java.io.File;
import java.io.IOException;

public class FileUploadHandler {

    public void upload_file(File p, String filename) {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File targetFile = new File(uploadsDir, filename);
        try {
            p.renameTo(targetFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        File file = new File("example.txt");
        FileUploadHandler handler = new FileUploadHandler();
        handler.upload_file(file, file.getName());
    }
}