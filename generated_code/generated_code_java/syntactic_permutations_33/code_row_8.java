import javax.servlet.http.*;
import java.io.*;

public class RedirectUrl extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    String url = request.getParameter("url");
    if (url == null || !url.startsWith("http://example.com/")) {
      response.setStatus(400); // Bad Request
      response.getWriter().println("Invalid URL: " + url);
      return;
    }
    response.sendRedirect(url);
  }
}