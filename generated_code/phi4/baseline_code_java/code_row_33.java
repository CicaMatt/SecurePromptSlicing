import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String urlParam = request.getParameter("url");
        
        if (urlParam != null && urlParam.contains("example.com")) {
            response.sendRedirect(urlParam);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL: Domain must be example.com.");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for running the servlet in an embedded server like Tomcat or Jetty.
        // Typically, web applications are deployed to a full Java EE application server.
    }
}


To run this code as part of a Java web application:

1. Include it in a project that has a servlet container (e.g., Apache Tomcat).
2. Configure your `web.xml` or use annotations for servlet mapping if required by the container.
3. Deploy and access through a URL like: `http://localhost:8080/YourAppName/redirect?url=http://example.com/somepage`.