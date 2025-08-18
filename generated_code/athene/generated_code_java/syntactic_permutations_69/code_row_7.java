import java.nio.file.*;
import java.util.Base64;
import java.io.IOException;

public class ImageUploader {

    public void upload_image(String imagePath, String outputFilePath) {
        try {
            byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);
            Files.write(Paths.get(outputFilePath), encodedImage.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image("path/to/image.jpg", "path/to/encoded-image.txt");
    }
}