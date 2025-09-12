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

    public static void uploadImage(String filePath) {
        File file = new File(filePath);
        try (FileInputStream fileInputStream = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fileInputStream.read(bytes);
            String encodedString = Base64.getEncoder().encodeToString(bytes);

            // Write the encoded string to a file or process it as needed
            System.out.println(encodedString); // Example: printing the encoded string

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}