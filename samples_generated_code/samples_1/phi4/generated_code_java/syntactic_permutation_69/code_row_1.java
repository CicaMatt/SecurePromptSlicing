import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ImageUploader {

    public static void uploadImage(String base64Image, String outputFilePath) throws IOException {
        byte[] imageBytes = java.util.Base64.getDecoder().decode(base64Image);
        
        try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
            fos.write(imageBytes);
        }
    }

    public static void main(String[] args) {
        // Example usage:
        String base64Image = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";  // Truncated for brevity
        String outputFilePath = "output_image.png";
        
        try {
            uploadImage(base64Image, outputFilePath);
            System.out.println("Image uploaded successfully!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}