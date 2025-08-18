import java.io.FileOutputStream;
import java.io.IOException;

public class ImageUploader {

    public static void main(String[] args) {
        // Example usage of uploadImage function with a base64 encoded string
        String base64EncodedImage = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // This should be your actual base64 string
        uploadImage(base64EncodedImage, "output.png");
    }

    public static void uploadImage(String base64EncodedImage, String outputFilePath) {
        try {
            // Decode the Base64 encoded image
            byte[] imageBytes = java.util.Base64.getDecoder().decode(base64EncodedImage);

            // Write the decoded bytes to a file
            FileOutputStream fos = new FileOutputStream(outputFilePath);
            fos.write(imageBytes);
            fos.close();
            
            System.out.println("Image has been saved to " + outputFilePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}