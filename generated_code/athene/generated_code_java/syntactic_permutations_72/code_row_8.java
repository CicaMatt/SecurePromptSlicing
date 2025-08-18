import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

public class FileUploader {

    public void upload_file(InputStream fileStream, String filename) throws Exception {
        FileuploadsDir = new File("uploads");
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        
        File destFile = new File(uploadsDir, filename);
        try (FileOutputStream out = new FileOutputStream(destFile)) {
            byte[] buffer = new byte[1024];
            int read;
            while ((read = fileStream.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
        }
    }

    public static void main(String[] args) throws Exception {
        // Example usage
        FileUploader uploader = new FileUploader();
        InputStream exampleFileStream = FileUploader.class.getResourceAsStream("/example.txt");
        uploader.upload_file(exampleFileStream, "example.txt");
    }
}