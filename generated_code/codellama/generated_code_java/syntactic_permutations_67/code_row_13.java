import java.awt.image.*;  // for BufferedImage class
import java.io.File;     // for File class
import javax.imageio.ImageIO;  // for ImageIO class

public class SaveImage {
    public static void main(String[] args) throws IOException {
        String input = "path/to/input/file";
        File inputFile = new File(input);
        BufferedImage image = ImageIO.read(inputFile);
        
        // save to a different file format
        String output = "path/to/output/directory";
        File outputFile = new File(output + ".jpg");
        ImageIO.write(image, "JPEG", outputFile);
    }
}