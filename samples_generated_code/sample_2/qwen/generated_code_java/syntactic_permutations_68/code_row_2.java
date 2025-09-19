import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Replace with actual image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String filePath) {
        File file = new File(filePath);
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fis.read(bytes);
            String base64String = Base64.getEncoder().encodeToString(bytes);
            processImage(file.getName(), base64String);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void processImage(String imageName, String base64String) {
        // Here you can add code to handle the image name and base64 string
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 String: " + base64String);
    }
}