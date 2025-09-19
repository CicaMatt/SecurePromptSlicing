import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public void uploadImage(String base64Image, String filePath) {
        try {
            // Decode the Base64 string
            byte[] decodedBytes = Base64.getDecoder().decode(base64Image);

            // Write the decoded bytes to a file
            FileOutputStream fos = new FileOutputStream(filePath);
            fos.write(decodedBytes);
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();

        // Example Base64 encoded image string (very small and not a valid image)
        String base64Image = "iVBORw0KGgoAAAANSUhEUgAAAAUA";
        String filePath = "output_image.png";

        uploader.uploadImage(base64Image, filePath);
    }
}