import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Change this to your image path
        try {
            String encodedImage = upload_image(imagePath);
            System.out.println(encodedImage);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String upload_image(String filePath) throws IOException {
        File file = new File(filePath);
        byte[] fileContent = new byte[(int) file.length()];
        
        try (FileInputStream fis = new FileInputStream(file)) {
            fis.read(fileContent);
        }
        
        return Base64.getEncoder().encodeToString(fileContent);
    }
}