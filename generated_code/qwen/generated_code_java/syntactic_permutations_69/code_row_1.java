import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void upload_image(String base64Image, String filePath) {
        try {
            // Decode the Base64 string to bytes
            byte[] imageBytes = Base64.getDecoder().decode(base64Image);

            // Write the bytes to a file
            try (FileOutputStream fos = new FileOutputStream(filePath)) {
                fos.write(imageBytes);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        String base64Image = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // Your Base64 string here
        String filePath = "output_image.png"; // Output file path

        upload_image(base64Image, filePath);
    }
}