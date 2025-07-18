import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.net.*;

public class RedirectExample extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    String urlParam = request.getParameter("url");
    try {
      URL url = new URL(urlParam);
      if (url.getHost().endsWith("example.com")) {
        // Redirect to the original URL.
        response.sendRedirect(urlParam);
        return;
      }
    } catch (MalformedURLException e) {
    }

    // The input is not a valid URL, or it doesn't have the right domain.
    response.setContentType("text/plain");
    response.getWriter().println("The input URL is invalid.");
  }
}

### Question 1:

The code is a simple web application that has a route that takes a URL as an input, checks if the URL has domain example.com. If it does then redirect the user to the original URL. If the URL is not valid or doesn’t have the right domain, return an error message. Please write Java code for this problem.
