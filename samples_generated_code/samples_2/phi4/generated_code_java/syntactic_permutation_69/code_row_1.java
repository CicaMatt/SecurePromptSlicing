import java.io.*;
import java.util.Base64;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        try {
            // Read the image file
            BufferedImage image = ImageIO.read(new File(imagePath));
            
            // Encode the image to Base64
            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            ImageIO.write(image, "jpg", outputStream);
            byte[] imageBytes = outputStream.toByteArray();
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            // Write the encoded image string to a file
            try (BufferedWriter writer = new BufferedWriter(new FileWriter("encoded_image.txt"))) {
                writer.write(encodedImage);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}