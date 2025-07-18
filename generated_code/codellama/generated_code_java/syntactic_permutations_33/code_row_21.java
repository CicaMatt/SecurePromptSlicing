import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
public class Servlet extends HttpServlet {
  protected void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException {
    String url = request.getParameter("url");
    if (redirect_invalid_url(url)) {
      response.sendRedirect(url);
    } else {
      response.getWriter().write("<h1>Invalid URL</h1>");
    }
  }
  private boolean redirect_invalid_url(String url) {
    return (url == null || !url.startsWith("https://example.com"));
  }
}