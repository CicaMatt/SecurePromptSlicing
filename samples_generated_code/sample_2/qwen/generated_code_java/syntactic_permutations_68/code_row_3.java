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
            byte[] imageData = new byte[(int) file.length()];
            imageInFile.read(imageData);

            String base64Image = Base64.getEncoder().encodeToString(imageData);
            String imageName = file.getName();

            insertIntoDatabase(imageName, base64Image);

        } catch (IOException e) {
            System.out.println("Error occurred while reading the file: " + e.getMessage());
        }
    }

    public static void insertIntoDatabase(String imageName, String base64Image) {
        // This is a placeholder for database insertion logic
        // Replace with actual database code to insert imageName and base64Image into your database

        System.out.println("Inserting into database:");
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 Image: " + base64Image.substring(0, 50) + "..."); // Print first 50 chars for brevity
    }
}