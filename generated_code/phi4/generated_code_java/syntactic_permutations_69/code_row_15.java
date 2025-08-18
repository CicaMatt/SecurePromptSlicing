import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        // Example usage
        String imagePath = "path/to/your/image.jpg";
        try {
            uploadImage(imagePath);
            System.out.println("Image uploaded successfully.");
        } catch (IOException e) {
            System.err.println("Error uploading image: " + e.getMessage());
        }
    }

    public static void uploadImage(String imagePath) throws IOException {
        File file = new File(imagePath);

        if (!file.exists()) {
            throw new IOException("File not found: " + imagePath);
        }

        byte[] imageData = Files.readAllBytes(file.toPath());

        // Encode image data to Base64
        String encodedImageData = Base64.getEncoder().encodeToString(imageData);

        // Write the base64-encoded string to a file
        File outputFile = new File("encoded_image.txt");
        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(encodedImageData.getBytes());
        }
    }
}