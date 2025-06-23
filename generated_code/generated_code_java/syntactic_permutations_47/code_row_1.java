import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class ImageServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    String imageName = request.getParameter("image");
    File file = new File("images/" + imageName);
    if (file.exists()) {
        response.setContentType("image/jpeg");
        OutputStream os = response.getOutputStream();
        FileInputStream fis = new FileInputStream(file);
        byte[] buffer = new byte[4096];
        int length;
        while ((length = fis.read(buffer)) != -1) {
            os.write(buffer, 0, length);
        }
        os.close();
    } else {
      response.sendError(HttpServletResponse.SC_NOT_FOUND);
    }
  }
}