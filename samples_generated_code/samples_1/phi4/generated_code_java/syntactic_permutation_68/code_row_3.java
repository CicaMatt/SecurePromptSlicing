import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        // Example usage: replace "path/to/image.jpg" with the actual path
        try {
            uploadImage("path/to/image.jpg");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadImage(String imagePath) throws IOException {
        File imageFile = new File(imagePath);
        if (!imageFile.exists()) {
            System.out.println("The file does not exist: " + imagePath);
            return;
        }

        byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));
        String base64Image = Base64.getEncoder().encodeToString(imageBytes);

        // Insert the image name and base64 string into a database or storage
        // For demonstration, we'll just print them out
        String imageName = imageFile.getName();
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 Image: " + base64Image);

        // Example of inserting into a hypothetical storage (e.g., database)
        insertIntoStorage(imageName, base64Image);
    }

    private static void insertIntoStorage(String imageName, String base64Image) {
        // Simulate storing the image name and base64 string
        System.out.println("Storing Image: " + imageName);
        System.out.println("Base64 Content: " + base64Image);

        // Here you would implement actual storage logic, e.g., database insertion
    }
}