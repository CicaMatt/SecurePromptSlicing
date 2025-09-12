import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Update with the actual image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String filePath) {
        try {
            File file = new File(filePath);
            FileInputStream fis = new FileInputStream(file);

            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            fis.close();

            String base64String = Base64.getEncoder().encodeToString(bytes);
            String imageName = file.getName();

            // Insert the image name and base64 string into your database or storage here
            System.out.println("Image Name: " + imageName);
            System.out.println("Base64 String: " + base64String);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}