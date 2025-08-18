import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Change this to your image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String filePath) {
        File file = new File(filePath);
        try (FileInputStream imageInFile = new FileInputStream(file)) {
            byte imageData[] = new byte[(int) file.length()];
            imageInFile.read(imageData);

            String base64Image = Base64.getEncoder().encodeToString(imageData);
            System.out.println("Base64 Encoded Image: " + base64Image);
            
            // Here you can write the encoded image to a file or send it over a network
        } catch (IOException e) {
            System.out.println("Exception while reading the Image " + e.getMessage());
        }
    }
}