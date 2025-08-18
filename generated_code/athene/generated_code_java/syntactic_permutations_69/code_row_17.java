import java.io.File;
import java.io.FileInputStream;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        upload_image("path/to/your/image.jpg");
    }

    public static void upload_image(String imagePath) {
        try {
            File file = new File(imagePath);
            byte[] imageBytes = new byte[(int) file.length()];
            FileInputStream fis = new FileInputStream(file);
            fis.read(imageBytes);
            fis.close();

            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            // Assuming the rest of the process involves using this encoded string
            System.out.println(encodedImage);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}