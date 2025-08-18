import java.io.FileOutputStream;
import java.io.IOException;

public class ImageUploader {

    public static void uploadImage(String base64EncodedImage, String filePath) {
        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            byte[] decodedBytes = javax.xml.bind.DatatypeConverter.parseBase64Binary(base64EncodedImage);
            fos.write(decodedBytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String base64EncodedImage = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // Example Base64 string
        String filePath = "uploaded_image.png";
        uploadImage(base64EncodedImage, filePath);
    }
}