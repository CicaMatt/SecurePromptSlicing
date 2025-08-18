import java.io.File;
import java.io.IOException;

public class FileUploader {

    public void upload_file(File file) {
        String filename = file.getName();
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File targetFile = new File(uploadsDir, filename);
        try {
            file.renameTo(targetFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        FileUploader fu = new FileUploader();
        File testFile = new File("test.txt");
        fu.upload_file(testFile);
    }
}