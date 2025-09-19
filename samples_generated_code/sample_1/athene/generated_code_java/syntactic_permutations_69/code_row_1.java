import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(String base64Image, String filePath) {
        byte[] decodedBytes = Base64.getDecoder().decode(base64Image);
        File file = new File(filePath);
        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(decodedBytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();
        String base64Image = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // Example Base64 string
        String filePath = "output_image.png";
        uploader.upload_image(base64Image, filePath);
    }
}