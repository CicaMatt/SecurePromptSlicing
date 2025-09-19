import java.io.File;
import java.io.IOException;

public class FileUploader {

    public void upload_file(File p) {
        String filename = p.getName();
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File destination = new File(uploadsDir, filename);
        try {
            p.renameTo(destination);
        } catch (SecurityException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        FileUploader uploader = new FileUploader();
        File fileToUpload = new File("example.txt");
        uploader.upload_file(fileToUpload);
    }
}