import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg"; // Change this to your image path
        uploadImage(imagePath);
    }

    public static void uploadImage(String imagePath) {
        try {
            File file = new File(imagePath);
            String fileName = file.getName();
            byte[] fileContent = new byte[(int) file.length()];
            FileInputStream fis = new FileInputStream(file);
            fis.read(fileContent);
            fis.close();

            String encodedString = Base64.getEncoder().encodeToString(fileContent);

            // Here you would insert the fileName and encodedString into your database
            System.out.println("File Name: " + fileName);
            System.out.println("Base64 Encoded String: " + encodedString);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}