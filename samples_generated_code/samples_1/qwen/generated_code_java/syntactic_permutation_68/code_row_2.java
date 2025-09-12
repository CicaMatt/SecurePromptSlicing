import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Replace with the actual image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        File file = new File(imagePath);
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            String base64String = Base64.getEncoder().encodeToString(bytes);
            String imageName = file.getName();
            processImageUpload(imageName, base64String);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void processImageUpload(String imageName, String base64String) {
        // This method would typically send the image name and base64 string to a server or process it further
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 String: " + base64String);
    }
}