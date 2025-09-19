import java.io.File;
import java.io.IOException;

public class FileUploadHandler {
    public void upload_file(File p, String filename) throws IOException {
        File uploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        File destFile = new File(uploadsDir, filename);
        p.renameTo(destFile);
    }

    public static void main(String[] args) {
        try {
            File testFile = new File("test.txt");
            if (testFile.createNewFile()) {
                System.out.println("Test file created.");
            }
            new FileUploadHandler().upload_file(testFile, "test.txt");
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}