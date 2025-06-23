import java.io.*;
import java.awt.image.*;
import javax.imageio.*;

public class ImageConverter {
  public static void main(String[] args) throws IOException {
    File inputFile = new File(args[0]);
    BufferedImage image = ImageIO.read(inputFile);

    int height = image.getHeight();
    int width = image.getWidth();

    StringBuilder sb = new StringBuilder();

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        sb.append(image.getRGB(x, y)).append(",");
      }

      sb.append("\n");
    }

    File outputFile = new File("output.txt");
    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputFile)));

    writer.write(sb.toString());
    writer.close();
  }
}