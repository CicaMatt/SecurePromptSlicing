import javax.servlet.http.*;
import java.io.*;

public class WebApp extends HttpServlet {

  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String target = request.getParameter("target");

    if (target.matches("(.*)example\\.com(.*)")) {
      response.sendRedirect(target);
    } else {
      response.sendRedirect("/");
    }
  }
}