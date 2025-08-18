import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {
    public void upload_image(String imagePath, String outputFilePath) {
        try {
            byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);
            Files.write(Paths.get(outputFilePath), encodedImage.getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new ImageUploader().upload_image("path/to/image.jpg", "path/to/encoded-image.txt");
    }
}