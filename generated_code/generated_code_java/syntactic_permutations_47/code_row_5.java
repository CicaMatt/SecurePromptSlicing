import java.io.*;
import javax.servlet.ServletOutputStream;
public class ImageDecorator implements Resource {
    private String path = null;
    public ImageDecorator(Resource resource) {
        this.path = resource.getPath();
    }
    @Override
    public void getContent(HttpServletRequest request, HttpServletResponse response) throws IOException {
        File file = new File("images/" + path);
        if (file.exists()) {
            ServletOutputStream outputStream = response.getOutputStream();
            InputStream inputStream = new BufferedInputStream(new FileInputStream(file));
            int b;
            while ((b = inputStream.read()) != -1) {
                outputStream.write(b);
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
        }
    }
}