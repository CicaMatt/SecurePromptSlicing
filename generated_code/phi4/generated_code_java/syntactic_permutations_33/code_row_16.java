import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "UrlRedirectServlet", urlPatterns = {"/redirect"})
public class UrlRedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String urlString = request.getParameter("url");
        
        if (isValidUrl(urlString)) {
            response.sendRedirect(urlString);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL.");
        }
    }

    private boolean isValidUrl(String url) {
        try {
            java.net.URL parsedUrl = new java.net.URL(url);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}


This code assumes you are using a servlet container like Apache Tomcat and have the appropriate `web.xml` configuration or use the `@WebServlet` annotation to define your servlet mapping. Make sure your project is set up as a web application in an IDE that supports Java EE, such as Eclipse or IntelliJ IDEA, with necessary libraries for servlets included.