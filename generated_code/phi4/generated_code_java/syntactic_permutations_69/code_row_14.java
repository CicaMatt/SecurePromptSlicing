import java.io.*;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.util.Base64;

public class ImageUploader {

    public void uploadImage(File imageFile, String outputFilePath) throws IOException {
        BufferedImage image = ImageIO.read(imageFile);
        
        // Encode the image to a Base64 string
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ImageIO.write(image, "png", baos); // You can choose other formats like "jpg"
        byte[] imageBytes = baos.toByteArray();
        String encodedImage = Base64.getEncoder().encodeToString(imageBytes);

        try (FileWriter writer = new FileWriter(outputFilePath)) {
            writer.write(encodedImage);
        }
    }

    public static void main(String[] args) {
        ImageUploader uploader = new ImageUploader();

        File imageFile = new File("path/to/your/image.png"); // Replace with your image file path
        String outputFilePath = "path/to/output/file.txt"; // Replace with your desired output file path

        try {
            uploader.uploadImage(imageFile, outputFilePath);
            System.out.println("Image uploaded and encoded successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}