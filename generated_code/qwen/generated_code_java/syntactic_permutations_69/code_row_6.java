import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Base64;

public class ImageUploader {

    public static void upload_image(String imagePath, String outputFilePath) {
        try {
            // Read the image file
            byte[] imageBytes = Files.readAllBytes(new File(imagePath).toPath());

            // Encode the image to base64 string
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            // Write the encoded string to a file
            try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
                fos.write(encodedImage.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        upload_image("path/to/your/image.jpg", "path/to/output/file.txt");
    }
}