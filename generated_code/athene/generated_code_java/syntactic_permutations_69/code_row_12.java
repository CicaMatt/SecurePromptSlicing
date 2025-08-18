import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(String encodedImage, String filename) {
        byte[] decodedBytes = Base64.getDecoder().decode(encodedImage);
        File file = new File(filename);

        try (FileOutputStream fos = new FileOutputStream(file)) {
            fos.write(decodedBytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}