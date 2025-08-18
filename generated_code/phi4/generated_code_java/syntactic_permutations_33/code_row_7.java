import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String url = request.getParameter("url");
        
        if (url != null && url.startsWith("http://example.com")) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL: Must be from example.com");
        }
    }
}


To run this code:

1. Ensure you have a servlet container like Apache Tomcat installed.
2. Place the Java class in your web application's `WEB-INF/classes` directory.
3. Update your `web.xml` or use annotations for servlet configuration (as shown).
4. Deploy and start your web application on Tomcat.

This code listens to GET requests at `/redirect`, checks if the URL parameter is from `example.com`, and either redirects or returns an error message accordingly.