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

            // Encode the image bytes to base64
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
        String imagePath = "path/to/your/image.jpg"; // Replace with your image path
        String outputFilePath = "path/to/output/base64.txt"; // Replace with your desired output file path

        upload_image(imagePath, outputFilePath);
    }
}