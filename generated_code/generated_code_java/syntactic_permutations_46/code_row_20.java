import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Img {
    @Decorator(path = "/img")
    public static File img(@Param String name) throws IOException {
        BufferedImage image = ImageIO.read(new File("assets/" + name));
        return new File(image);
    }
}