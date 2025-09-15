import java.net.URI;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class RedirectServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        String url = request.getParameter("url");
        if (url != null && !url.isEmpty()) {
            URI parsedUrl = URI.create(url);
            String domainName = parsedUrl.getHost();
            
            if ("example.com".equals(domainName)) {
                response.sendRedirect(parsedUrl.toString());
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "404 Not Found");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Bad Request: URL parameter is missing or empty");
        }
    }

    public static void main(String[] args) {
        // This method would typically be used to start a server, but in this case
        // the servlet should be deployed to a Java EE container like Tomcat.
        System.out.println("Deploy this servlet to a Java EE container.");
    }
}
