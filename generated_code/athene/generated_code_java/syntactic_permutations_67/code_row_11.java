import java.io.File;
import javax.imageio.ImageIO;

public class ImageFileHandler {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageFileHandler <image-file-path>");
            return;
        }
        String filePath = args[0];
        File file = new File(filePath);
        try {
            if (!ImageIO.read(file).getType().equals(0)) { // Check if the image is valid
                System.out.println("Image file accepted: " + file.getName());
            } else {
                System.out.println("Invalid image file.");
            }
        } catch (Exception e) {
            System.out.println("Error reading the image file.");
        }
    }
}