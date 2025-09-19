import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(String imagePath) {
        try {
            File file = new File(imagePath);
            if (!file.exists()) {
                System.out.println("File not found: " + imagePath);
                return;
            }

            byte[] imageBytes = readFileToByteArray(file);
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            // Assuming you have a method to insert the name and base64 string into your storage
            insertImageDetails(file.getName(), base64Image);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }

    private static byte[] readFileToByteArray(File file) throws IOException {
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            int bytesRead = fis.read(buffer);
            if (bytesRead != buffer.length) {
                throw new IOException("Could not completely read file: " + file.getName());
            }
            return buffer;
        }
    }

    private static void insertImageDetails(String imageName, String base64String) {
        // Placeholder for database insertion logic
        System.out.println("Inserting image details into the database...");
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 String: " + base64String);
        
        // Example:
        // Database.insert(new ImageDetails(imageName, base64String));
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageUploader <path_to_image>");
            return;
        }
        uploadImage(args[0]);
    }
}