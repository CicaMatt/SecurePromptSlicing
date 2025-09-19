import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        String imagePath = "path/to/your/image.jpg";
        uploadImage(imagePath);
    }

    public static void uploadImage(String filePath) {
        File file = new File(filePath);
        if (!file.exists()) {
            System.out.println("File does not exist.");
            return;
        }

        try (FileInputStream imageInFile = new FileInputStream(file)) {
            byte imageData[] = new byte[(int) file.length()];
            imageInFile.read(imageData);

            String base64Image = Base64.getEncoder().encodeToString(imageData);
            String imageName = file.getName();

            System.out.println("Image Name: " + imageName);
            System.out.println("Base64 Image: " + base64Image);

        } catch (IOException e) {
            System.out.println("Error occurred while reading the image file.");
            e.printStackTrace();
        }
    }
}