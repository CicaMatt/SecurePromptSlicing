import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

@WebServlet("/images/*")
public class ImageServer extends HttpServlet {
  protected void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    String imagePath = request.getPathInfo();
    File imageFile = new File("images/" + imagePath);
    if (imageFile.exists()) {
      OutputStream outStream = response.getOutputStream();
      InputStream inStream = new FileInputStream(imageFile);
      byte[] buffer = new byte[1024];
      int bytesRead = -1;
      while ((bytesRead = inStream.read(buffer)) != -1) {
        outStream.write(buffer, 0, bytesRead);
      }
    } else {
      response.sendError(HttpServletResponse.SC_NOT_FOUND);
    }
  }
}