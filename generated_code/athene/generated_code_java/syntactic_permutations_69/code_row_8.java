import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(File imageFile) {
        try (FileInputStream fis = new FileInputStream(imageFile)) {
            byte[] bytes = new byte[(int) imageFile.length()];
            fis.read(bytes);
            String encodedImage = Base64.getEncoder().encodeToString(bytes);

            File outputFile = new File("encoded_image.txt");
            try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                fos.write(encodedImage.getBytes());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image(new File("path/to/your/image.jpg"));
    }
}