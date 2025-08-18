import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static String uploadImage(String imagePath) {
        File file = new File(imagePath);
        if (!file.exists()) {
            throw new IllegalArgumentException("File not found: " + imagePath);
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] imageBytes = new byte[(int) file.length()];
            int bytesRead = fis.read(imageBytes);

            if (bytesRead != imageBytes.length) {
                throw new IOException("Could not completely read the file.");
            }

            return Base64.getEncoder().encodeToString(imageBytes);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        String base64Image = uploadImage(imagePath);

        if (base64Image != null) {
            System.out.println("Encoded Image: " + base64Image);
        } else {
            System.out.println("Failed to encode image.");
        }
    }
}