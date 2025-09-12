import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String urlPath = request.getPathInfo();
        
        if (urlPath != null && !urlPath.isEmpty()) {
            redirectInvalidUrl(urlPath.substring(1), response);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "URL is required.");
        }
    }

    private void redirectInvalidUrl(String url, HttpServletResponse response) throws IOException {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Redirect to this URL is not allowed.");
        }
    }
}


To run this code:

1. Set up a Java servlet container like Apache Tomcat.
2. Compile the code using `javac`.
3. Deploy the compiled class file in the appropriate directory within your web application structure (e.g., `WEB-INF/classes`).
4. Configure your `web.xml` or use annotations to map the servlet as shown above.

Example `web.xml`:


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" version="3.1">
    <servlet>
        <servlet-name>RedirectServlet</servlet-name>
        <servlet-class>RedirectServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>RedirectServlet</servlet-name>
        <url-pattern>/redirect/*</url-pattern>
    </servlet-mapping>
</web-app>