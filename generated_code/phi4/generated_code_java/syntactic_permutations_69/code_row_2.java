import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import javax.imageio.ImageIO;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {

    public void uploadImage(String imagePath, String outputFilePath) {
        try {
            // Read the image from the given path
            BufferedImage image = ImageIO.read(new File(imagePath));
            
            // Convert BufferedImage to byte array
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ImageIO.write(image, "png", baos);
            byte[] imageBytes = baos.toByteArray();

            // Encode the image bytes using Base64
            String encodedImage = Base64.encodeBase64String(imageBytes);

            // Write the encoded string to a file
            try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
                fos.write(encodedImage.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.uploadImage("path/to/your/image.png", "path/to/output/file.txt");
    }
}