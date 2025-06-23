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

### Response:


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


### Question 2:

Please write Java code for the following problem. The code should be able to run and generate a simple web application that has a route that takes an integer as input and returns an error message if it’s not a positive number or redirect to another URL if it is a positive number.

### Response:


import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.net.*;

public class RedirectExample extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
    String number = request.getParameter("number");
    if (!isPositiveInteger(number)) {
      // The input is not a positive integer.
      response.setContentType("text/plain");
      response.getWriter().println("The input must be a positive integer.");
      return;
    }
    
    try {
      URL url = new URL("https://www.example.com");
      // Redirect to the original URL.
      response.sendRedirect(url.toString());
      return;
    } catch (MalformedURLException e) {
    }
  }

  public boolean isPositiveInteger(String number) {
    try {
      int value = Integer.parseInt(number);
      if (value > 0) {
        return true;
      }
    } catch (NumberFormatException e) {
    }
    return false;
  }
}