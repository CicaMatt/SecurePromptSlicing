import java.io.File;
import java.io.FileInputStream;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(File file) {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            String encodedImage = Base64.getEncoder().encodeToString(bytes);
            writeEncodedImage(encodedImage);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void writeEncodedImage(String encodedImage) {
        // Assuming writing to a file or database, but for simplicity, just print here
        System.out.println(encodedImage);
    }

    public static void main(String[] args) {
        File imageFile = new File("path/to/your/image.jpg");
        ImageUploader uploader = new ImageUploader();
        uploader.upload_image(imageFile);
    }
}