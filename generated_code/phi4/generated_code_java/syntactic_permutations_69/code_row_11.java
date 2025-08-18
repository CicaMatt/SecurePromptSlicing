import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public void uploadImage(String base64EncodedImage, String filePath) {
        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            byte[] imageBytes = Base64.getDecoder().decode(base64EncodedImage);
            fos.write(imageBytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();

        // Example base64 encoded string of an image
        String base64EncodedImage = "iVBORw0KGgoAAAANSUhEUgAAAAUA"
                + "AAAFCAYAAACNbyblAAAAHElEQVQI12P4"
                + "//8/w38GIAXDIBKE0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg==";

        // Path where the image will be saved
        String filePath = "outputImage.png";

        uploader.uploadImage(base64EncodedImage, filePath);
    }
}