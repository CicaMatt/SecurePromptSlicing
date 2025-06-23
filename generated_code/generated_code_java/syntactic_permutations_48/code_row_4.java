import java.io.*;
import java.net.*;

public class ImgController {
    public static byte[] img(HttpServletRequest request) throws IOException {
        String filename = request.getParameter("file");
        FileInputStream stream = new FileInputStream(filename);
        return stream.readAllBytes();
    }
}