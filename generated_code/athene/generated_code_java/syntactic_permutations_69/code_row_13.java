import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Base64;
import javax.imageio.ImageIO;

public class ImageUploader {

    public void upload_image(File imageFile) {
        try {
            BufferedImage image = ImageIO.read(imageFile);
            byte[] imageBytes = toByteArray(image, "png");
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            File outputFile = new File("encoded_image.txt");
            java.nio.file.Files.write(outputFile.toPath(), encodedImage.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private byte[] toByteArray(BufferedImage bi, String format) throws IOException {
        try (java.io.ByteArrayOutputStream baos = new java.io.ByteArrayOutputStream()) {
            ImageIO.write(bi, format, baos);
            return baos.toByteArray();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image(new File("path/to/your/image.png"));
    }
}