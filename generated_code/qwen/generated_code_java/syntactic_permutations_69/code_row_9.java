import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Base64;

public class ImageUploader {

    public static void upload_image(String filePath) {
        try {
            // Read the image file
            byte[] imageBytes = Files.readAllBytes(new File(filePath).toPath());

            // Encode the image to base64 string
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            // Write the base64 encoded string to a file
            FileOutputStream writer = new FileOutputStream("encoded_image.txt");
            writer.write(encodedImage.getBytes());
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        upload_image("path_to_your_image.jpg");
    }
}