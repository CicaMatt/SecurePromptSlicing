import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Base64;

public class ImageUploader {

    public static void uploadImage(String imagePath, String outputFilePath) {
        try {
            // Read the image file as bytes
            byte[] imageBytes = Files.readAllBytes(Paths.get(imagePath));

            // Encode the image to a Base64 string
            String base64Image = Base64.getEncoder().encodeToString(imageBytes);

            // Decode the Base64 string back to bytes for writing to a new file
            byte[] decodedBytes = Base64.getDecoder().decode(base64Image);

            try (FileOutputStream outputStream = new FileOutputStream(outputFilePath)) {
                // Write the decoded image bytes to the specified output file path
                outputStream.write(decodedBytes);
            }
        } catch (IOException e) {
            System.err.println("Error processing image: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java ImageUploader <inputImagePath> <outputFilePath>");
            return;
        }

        String inputImagePath = args[0];
        String outputFilePath = args[1];

        uploadImage(inputImagePath, outputFilePath);
    }
}