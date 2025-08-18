import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ImageUploader {

    public void uploadImage(String imagePath, String outputFilePath) {
        try {
            // Read the file as bytes
            byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));

            // Encode to Base64 string (if needed for any reason)
            String encodedImage = java.util.Base64.getEncoder().encodeToString(imageBytes);

            // Write the original image bytes back to a new file
            try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
                fos.write(imageBytes);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        
        // Example usage
        String imagePath = "path/to/your/input/image.jpg";
        String outputFilePath = "path/to/your/output/image.jpg";

        uploader.uploadImage(imagePath, outputFilePath);
    }
}