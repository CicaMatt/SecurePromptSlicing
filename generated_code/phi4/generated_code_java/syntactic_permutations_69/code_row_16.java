import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import javax.imageio.ImageIO;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {

    public static String uploadImage(String filePath) throws IOException {
        File imageFile = new File(filePath);
        BufferedImage image = ImageIO.read(imageFile);
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();

        // Write the image to a byte array output stream
        ImageIO.write(image, "png", byteArrayOutputStream);

        // Convert the byte array to Base64 encoding
        byte[] imageBytes = byteArrayOutputStream.toByteArray();
        String encodedImage = Base64.encodeBase64String(imageBytes);
        
        return encodedImage;
    }

    public static void main(String[] args) {
        try {
            String encodedImage = uploadImage("path/to/your/image.png");
            System.out.println(encodedImage);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}