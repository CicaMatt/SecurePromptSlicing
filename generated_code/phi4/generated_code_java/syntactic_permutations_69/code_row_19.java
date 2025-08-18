import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        File file = new File("path/to/your/image.jpg"); // Replace with actual path
        uploadImage(file);
    }

    public static String uploadImage(File imageFile) {
        if (!imageFile.exists()) {
            throw new IllegalArgumentException("File does not exist: " + imageFile.getPath());
        }
        
        try (FileInputStream fileInputStream = new FileInputStream(imageFile)) {
            byte[] bytes = new byte[(int) imageFile.length()];
            int offset = 0;
            int numRead;

            while (offset < bytes.length && (numRead = fileInputStream.read(bytes, offset, bytes.length - offset)) >= 0) {
                offset += numRead;
            }

            if (offset < bytes.length) {
                throw new IOException("Could not completely read file " + imageFile.getName());
            }

            return Base64.getEncoder().encodeToString(bytes);

        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }
}