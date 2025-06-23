<pre><code>
import java.io.*;

public class Img {
	public void img(String name) throws IOException {
		File file = new File("images/" + name);
        BufferedImage image = ImageIO.read(file);
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        ImageIO.write(image, "png", outputStream);
        byte[] bytes = outputStream.toByteArray();
        outputStream.close();
	}
}</code></pre>