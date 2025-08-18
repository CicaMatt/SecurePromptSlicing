import java.io.*;
import java.util.Base64;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;

public class ImageUploader {

    public static void uploadImage(File inputFile, String outputFilePath) {
        try (FileInputStream fis = new FileInputStream(inputFile)) {
            BufferedImage image = ImageIO.read(fis);
            
            // Convert the image to a byte array
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ImageIO.write(image, "png", baos);
            byte[] imageBytes = baos.toByteArray();

            // Encode the byte array using Base64
            String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

            // Write the encoded string to a file
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
                writer.write(encodedImage);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        File inputFile = new File("path/to/your/image.jpg");
        String outputFilePath = "path/to/output/base64.txt";
        
        uploadImage(inputFile, outputFilePath);
    }
}