import java.io.File;
import java.io.IOException;

public class FileUploader {
    public void uploadFile(String filename) {
        File p = new File(filename);
        try {
            p.renameTo(new File("uploads" + File.separator + p.getName()));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        FileUploader uploader = new FileUploader();
        uploader.uploadFile(args[0]);
    }
}