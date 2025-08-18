import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(File uploadedImage, File destination) {
        try (FileInputStream fis = new FileInputStream(uploadedImage)) {
            byte[] imageBytes = new byte[(int) uploadedImage.length()];
            fis.read(imageBytes);
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            byte[] decodedImage = Base64.getDecoder().decode(encodedImage);
            try (FileOutputStream fos = new FileOutputStream(destination)) {
                fos.write(decodedImage);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        File uploadedImage = new File("path/to/uploaded/image.jpg");
        File destination = new File("path/to/destination/image.jpg");
        uploader.upload_image(uploadedImage, destination);
    }
}