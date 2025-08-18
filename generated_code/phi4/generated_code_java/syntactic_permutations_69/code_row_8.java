import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import javax.xml.bind.DatatypeConverter;

public class ImageUploader {

    public static void uploadImage(File inputFile, String outputFilePath) {
        try {
            byte[] imageBytes = Files.readAllBytes(inputFile.toPath());
            String encodedImage = DatatypeConverter.printBase64Binary(imageBytes);

            try (FileOutputStream fos = new FileOutputStream(outputFilePath)) {
                fos.write(encodedImage.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        File inputFile = new File("path/to/your/image.jpg");
        String outputFilePath = "path/to/output/file.txt";

        uploadImage(inputFile, outputFilePath);
    }
}