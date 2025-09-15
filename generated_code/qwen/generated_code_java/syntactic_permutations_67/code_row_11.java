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
