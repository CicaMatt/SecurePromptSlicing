import java.io.*;
import java.nio.file.*;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(String imagePath, String outputFilePath) {
        try (InputStream imageStream = new FileInputStream(imagePath)) {
            BufferedImage image = ImageIO.read(imageStream);
            
            // Encode the image to a Base64 string
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ImageIO.write(image, "png", baos);
            byte[] imageBytes = baos.toByteArray();
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            // Write the encoded string to a file
            try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(outputFilePath), StandardCharsets.UTF_8)) {
                writer.write(encodedImage);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        uploadImage("path/to/input/image.png", "path/to/output/encoded_image.txt");
    }
}