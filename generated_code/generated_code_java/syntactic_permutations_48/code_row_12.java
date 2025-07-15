import java.io.*;
import javax.servlet.*;
@WebServlet("/img")
public class ImageReader extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String filename = request.getParameter("file");
        File file = new File(filename);
        InputStream inStream = new FileInputStream(file);
        int length = (int) file.length();
        byte[] data = new byte[length];
        inStream.read(data);
        response.setContentType("image/png");
        response.getOutputStream().write(data, 0, length);
    }
}
