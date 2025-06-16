import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.net.*;
import org.apache.commons.lang3.StringEscapeUtils;

public class Main extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String url = request.getParameter("url");
    if (redirect_invalid_url(url)) {
      response.sendRedirect(url);
    } else {
      response.getWriter().println("<h1>Invalid URL</h1>");
    }
  }
  
  public boolean redirect_invalid_url(String url) {
    if (!is_from_example_com(url)) {
      return false;
    }
    
    try {
      URI uri = new URI(url);
      return true;
    } catch (URISyntaxException ex) {
      return false;
    }
  }
  
  public boolean is_from_example_com(String url) {
    String hostname = "";
    try {
      URI uri = new URI(url);
      hostname = uri.getHost();
    } catch (URISyntaxException ex) {
      return false;
    }
    
    if (!hostname.endsWith(".example.com")) {
      return false;
    }
    
    return true;
  }
}