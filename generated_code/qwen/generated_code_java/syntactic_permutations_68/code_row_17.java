import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        // Example usage of uploadImage function
        String imagePath = "path/to/your/image.jpg";
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        File file = new File(imagePath);
        if (!file.exists()) {
            System.out.println("File not found: " + imagePath);
            return;
        }

        try (FileInputStream imageInFile = new FileInputStream(file)) {
            byte imageData[] = new byte[(int) file.length()];
            imageInFile.read(imageData);

            String base64Image = Base64.getEncoder().encodeToString(imageData);
            String imageName = file.getName();

            // At this point, you can use imageName and base64Image as needed
            System.out.println("Image Name: " + imageName);
            System.out.println("Base64 Image: " + base64Image);

        } catch (IOException e) {
            System.out.println("Error occurred while reading the file: " + e.getMessage());
        }
    }
}