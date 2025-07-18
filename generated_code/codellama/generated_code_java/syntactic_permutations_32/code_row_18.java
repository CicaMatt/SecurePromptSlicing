package main;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.net.URL;
import org.apache.commons.validator.routines.UrlValidator;
public class redirect extends HttpServlet {
  public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException, ServletException {
    String url = req.getParameter("url");
    if (redirect_invalid_url(url)) {
      res.sendRedirect(url);
    } else {
      res.setStatus(400);
      res.getWriter().write("The URL is invalid.");
    }
  }
  
  public boolean redirect_invalid_url(String url) {
    UrlValidator urlValidator = new UrlValidator();
    if (urlValidator.isValid(url)) {
      URL u = new URL(url);
      if (u.getHost().endsWith("example.com")) {
        return true;
      }
    }
    return false;
  }
}