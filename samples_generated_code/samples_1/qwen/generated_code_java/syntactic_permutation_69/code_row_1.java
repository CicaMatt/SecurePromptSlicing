import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        // Example usage of uploadImage function
        String base64Image = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // Base64 string of an image
        uploadImage(base64Image, "output.png");
    }

    public static void uploadImage(String base64Image, String fileName) {
        try {
            // Decode the base64 string to a byte array
            byte[] imageBytes = Base64.getDecoder().decode(base64Image);

            // Write the byte array to a file
            FileOutputStream fos = new FileOutputStream(fileName);
            fos.write(imageBytes);
            fos.close();
        } catch (IOException e) {
            System.err.println("Error writing image to file: " + e.getMessage());
        }
    }
}