import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public String upload_image(File file) {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            return Base64.getEncoder().encodeToString(bytes);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args) {
        File imageFile = new File("path/to/your/image.jpg");
        ImageUploader uploader = new ImageUploader();
        String encodedImage = uploader.upload_image(imageFile);
        System.out.println(encodedImage);
    }
}