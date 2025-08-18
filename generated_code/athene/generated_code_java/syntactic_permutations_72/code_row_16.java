import java.io.File;
import java.io.IOException;

public class FileUploadHandler {

    public void upload(File p, String name) {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File dest = new File(uploadsDir, name);
        try {
            p.renameTo(dest);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        File fakeFile = new File("test.txt"); // Just for demonstration
        new FileUploadHandler().upload(fakeFile, "test.txt");
    }
}