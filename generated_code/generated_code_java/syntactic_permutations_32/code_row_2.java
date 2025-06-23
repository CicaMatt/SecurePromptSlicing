import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Redirect extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String url = request.getParameter("url");
    redirect_invalid_url(url);
  }
  
  private static void redirect_invalid_url(String url) {
    if(!url.startsWith("http://www.example.com/")) {
      System.out.println("Invalid URL.");
    } else {
      // Redirect user to the URL
    }
  }
}