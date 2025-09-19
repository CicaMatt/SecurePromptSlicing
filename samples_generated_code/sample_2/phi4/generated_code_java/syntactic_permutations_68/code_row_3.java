import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Base64;

public class ImageUploader {

    public static void main(String[] args) {
        try {
            String imageName = "example.jpg";
            uploadImage(imageName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadImage(String imageName) throws IOException {
        File imageFile = new File(imageName);

        if (!imageFile.exists()) {
            System.out.println("File not found: " + imageName);
            return;
        }

        FileInputStream fis = new FileInputStream(imageFile);
        byte[] byteArray = new byte[(int) imageFile.length()];
        int bytesCount = 0;

        while ((bytesCount = fis.read(byteArray)) != -1) {}

        String base64Image = Base64.getEncoder().encodeToString(byteArray);

        // Here you would insert the imageName and base64Image into your desired storage
        System.out.println("Image Name: " + imageName);
        System.out.println("Base64 Image: " + base64Image);

        fis.close();
    }
}