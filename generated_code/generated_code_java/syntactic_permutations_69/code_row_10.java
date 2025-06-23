import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {
    public static void upload_image(String image_path) throws IOException {
        FileInputStream inputStream = new FileInputStream(image_path);
        byte[] fileBytes = new byte[inputStream.available()];
        inputStream.read(fileBytes);
        String encodedString = Base64.getEncoder().encodeToString(fileBytes);

        FileOutputStream outputStream = new FileOutputStream("encodedImage.txt");
        outputStream.write(encodedString.getBytes());
    }
}