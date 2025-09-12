import java.nio.file.*;
import java.util.Base64;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.IOException;

public class ImageUploader {

    public void upload_image(Path imagePath) {
        try {
            BufferedImage image = ImageIO.read(imagePath.toFile());
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ImageIO.write(image, "png", baos);
            byte[] imageBytes = baos.toByteArray();
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            Path outputFilePath = imagePath.resolveSibling(imagePath.getFileName().toString() + ".base64");
            Files.writeString(outputFilePath, encodedImage);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image(Paths.get(args[0]));
    }
}