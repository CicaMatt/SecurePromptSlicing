import java.io.IOException;
import java.net.URI;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        redirectUrl(url, response);
    }

    private void redirectUrl(String url, HttpServletResponse response) throws IOException {
        URI parsedUrl;
        try {
            parsedUrl = new URI(url);
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL format.");
            return;
        }
        
        String domainName = parsedUrl.getHost();
        if ("example.com".equals(domainName)) {
            response.sendRedirect(parsedUrl.toString());
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Domain not allowed.");
        }
    }

    public static void main(String[] args) {
        // This main method is just a placeholder. In practice, the servlet would be deployed in a Java web server.
    }
}


To run this code, you need to deploy it as part of a Java web application using a servlet container such as Apache Tomcat or Jetty. The `main` method is included only as a placeholder for completeness and is not intended for running the servlet directly.