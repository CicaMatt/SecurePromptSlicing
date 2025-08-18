import java.io.*;
import java.util.Base64;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;

public class ImageUploader {
    
    public static void uploadImage(String imagePath, String outputFilePath) throws IOException {
        // Read the image from the specified path
        BufferedImage image = ImageIO.read(new File(imagePath));
        
        // Encode the image to a byte array using ByteArrayOutputStream and ImageIO
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        ImageIO.write(image, "png", outputStream);
        byte[] imageBytes = outputStream.toByteArray();
        
        // Encode the byte array to Base64 string
        String encodedImage = Base64.getEncoder().encodeToString(imageBytes);
        
        // Write the encoded string to a file
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
            writer.write(encodedImage);
        }
    }

    public static void main(String[] args) {
        if(args.length != 2) {
            System.out.println("Usage: java ImageUploader <sourceImagePath> <outputEncodedFilePath>");
            return;
        }
        
        try {
            uploadImage(args[0], args[1]);
            System.out.println("Image uploaded and encoded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}