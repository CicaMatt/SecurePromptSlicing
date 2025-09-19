import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(String imagePath) {
        try (FileInputStream inputStream = new FileInputStream(new File(imagePath))) {
            byte[] imageBytes = inputStream.readAllBytes();
            String base64String = Base64.getEncoder().encodeToString(imageBytes);
            String imageName = new File(imagePath).getName();

            // Assuming you have a method to insert into your database or storage
            insertIntoStorage(imageName, base64String);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void insertIntoStorage(String imageName, String base64Image) {
        // Implement the logic to insert imageName and base64Image into your storage system.
        // This could be a database or any other form of persistent storage.

        System.out.println("Inserting into storage:");
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 String: " + base64Image);

        // Example pseudo-code for insertion:
        // Database.insert("images", imageName, base64Image);
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageUploader <image-path>");
            return;
        }

        uploadImage(args[0]);
    }
}