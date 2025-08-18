import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Change this path to your image location
        uploadImage(imagePath);
    }

    public static void uploadImage(String filePath) {
        File file = new File(filePath);
        try (FileInputStream fileInputStream = new FileInputStream(file)) {
            byte[] bytes = new byte[(int) file.length()];
            fileInputStream.read(bytes);
            String encodedString = Base64.getEncoder().encodeToString(bytes);

            // Here you can write the encoded string to a file, database, or any other storage
            System.out.println(encodedString); // For demonstration, printing the base64 string

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}