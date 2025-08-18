import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        upload_image("input.jpg", "output.txt");
    }

    public static void upload_image(String imagePath, String outputFilePath) {
        try {
            byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);
            Files.write(Paths.get(outputFilePath), encodedImage.getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}