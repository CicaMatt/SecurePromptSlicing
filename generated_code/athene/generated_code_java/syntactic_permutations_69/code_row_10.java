import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(File imageFile) {
        try (FileInputStream fis = new FileInputStream(imageFile);
             FileOutputStream fos = new FileOutputStream("encodedImage.txt")) {

            byte[] imageBytes = new byte[(int) imageFile.length()];
            fis.read(imageBytes);
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            fos.write(encodedImage.getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new ImageUploader().upload_image(new File(args[0]));
    }
}