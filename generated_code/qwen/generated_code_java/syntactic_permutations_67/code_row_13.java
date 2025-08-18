import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class ImageSaver {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java ImageSaver <inputImageFile> <outputImagePath>");
            return;
        }

        String inputFilePath = args[0];
        String outputFilePath = args[1];

        File inputFile = new File(inputFilePath);
        File outputFile = new File(outputFilePath);

        try {
            javax.imageio.ImageIO.write(ImageIO.read(inputFile), "jpg", outputFile);
            System.out.println("Image saved successfully.");
        } catch (IOException e) {
            System.err.println("Error occurred while saving the image: " + e.getMessage());
        }
    }
}