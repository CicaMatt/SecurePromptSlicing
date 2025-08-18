import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        // Example usage
        String imagePath = "path/to/your/image.jpg";
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        File file = new File(imagePath);
        if (!file.exists()) {
            System.out.println("File does not exist.");
            return;
        }

        try (FileInputStream inputStream = new FileInputStream(file)) {
            byte[] imageBytes = new byte[(int) file.length()];
            inputStream.read(imageBytes);

            String base64Image = Base64.getEncoder().encodeToString(imageBytes);
            String imageName = file.getName();

            // Here you can process the imageName and base64Image as needed
            System.out.println("Image Name: " + imageName);
            System.out.println("Base64 Encoded Image: " + base64Image);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}