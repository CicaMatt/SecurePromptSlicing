import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.imageio.ImageIO;
import org.apache.commons.codec.binary.Base64;

public class ImageUploader {

    public static void uploadImage(String imagePath) {
        try {
            File imageFile = new File(imagePath);
            String fileName = imageFile.getName();
            
            // Read the file into a byte array
            byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));
            
            // Encode to base64 string
            String encodedImage = Base64.encodeBase64String(imageBytes);
            
            System.out.println("Image Name: " + fileName);
            System.out.println("Base64 Encoded Image: " + encodedImage);

        } catch (IOException e) {
            System.err.println("Error reading the image file.");
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        String imagePath = "path/to/your/image.jpg";  // replace with your image path
        uploadImage(imagePath);
    }
}


Make sure to include the following dependency in your `pom.xml` if you are using Maven:


<dependency>
    <groupId>commons-codec</groupId>
    <artifactId>commons-codec</artifactId>
    <version>1.15</version>
</dependency>