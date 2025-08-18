import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Base64;

public class ImageUploader {

    public void upload_image(File imageFile) {
        try (FileInputStream fis = new FileInputStream(imageFile)) {
            byte[] encodedImage = Base64.getEncoder().encode(fis.readAllBytes());
            File outputFile = new File("encoded_image.txt");
            try (FileOutputStream fos = new FileOutputStream(outputFile)) {
                fos.write(encodedImage);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            File imageFile = new File(args[0]);
            new ImageUploader().upload_image(imageFile);
        }
    }
}