import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class ImageDisplayer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ImageDisplayer <image-file-path>");
            return;
        }

        String imagePath = args[0];
        File imageFile = new File(imagePath);

        try {
            BufferedImage image = ImageIO.read(imageFile);
            if (image == null) {
                System.out.println("The file is not a recognized image format.");
                return;
            }
            displayImage(image, imageFile.getName());
        } catch (IOException e) {
            System.out.println("Error reading the image file: " + e.getMessage());
        }
    }

    private static void displayImage(BufferedImage img, String title) {
        JFrame frame = new JFrame(title);
        JLabel label = new JLabel(new ImageIcon(img));
        frame.getContentPane().add(label);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}



<!-- pom.xml for Maven project -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>ImageDisplayer</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <!-- No additional dependencies are required for this simple Java application -->
    </dependencies>
</project>