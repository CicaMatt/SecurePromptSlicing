import java.io.File;
import java.io.IOException;

public class FileUploader {
    public void handleFileUpload(File file, String filename) throws IOException {
        File uploadDir = new File("uploads");
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }
        File destFile = new File(uploadDir, filename);
        file.renameTo(destFile);
    }

    public static void main(String[] args) throws IOException {
        File tempFile = new File("temp.txt"); // Assume this is the file to be uploaded
        String fileName = "example.txt";
        new FileUploader().handleFileUpload(tempFile, fileName);
    }
}