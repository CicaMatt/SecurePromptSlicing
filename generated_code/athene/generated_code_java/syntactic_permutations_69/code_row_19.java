import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(String imagePath) {
        try {
            Path path = Paths.get(imagePath);
            byte[] imageBytes = Files.readAllBytes(path);
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            // Assuming you want to write the encoded string to a file
            Path outputFilePath = Paths.get("encoded_image.txt");
            Files.write(outputFilePath, encodedImage.getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image("path/to/your/image.jpg");
    }
}