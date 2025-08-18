import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class ImageProcessor {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageProcessor <image-file-path>");
            return;
        }

        String imagePath = args[0];
        File imageFile = new File(imagePath);

        try {
            BufferedImage bufferedImage = ImageIO.read(imageFile);
            if (bufferedImage == null) {
                System.out.println("The specified file is not a valid image.");
                return;
            }
            
            // Process the image as needed
            System.out.println("Image successfully loaded and processed:");
            System.out.println("Width: " + bufferedImage.getWidth());
            System.out.println("Height: " + bufferedImage.getHeight());

        } catch (Exception e) {
            System.err.println("Error processing the image file.");
            e.printStackTrace();
        }
    }
}