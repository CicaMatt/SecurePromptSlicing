import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ImageUploader {

    public static void uploadImage(String imagePath, String outputFilePath) {
        try {
            // Read the image file as bytes
            byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));

            // Convert the image bytes to a Base64 encoded string (not stored, just for demonstration)
            String base64EncodedString = java.util.Base64.getEncoder().encodeToString(imageBytes);

            // Write the original image bytes directly to the output file
            try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
                fos.write(imageBytes);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Replace with your image path
        String outputFilePath = "path/to/output/image.jpg"; // Replace with desired output file path

        uploadImage(imagePath, outputFilePath);
    }
}