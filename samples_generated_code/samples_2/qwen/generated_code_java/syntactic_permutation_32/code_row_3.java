import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {
    private static final String ALLOWED_DOMAIN = "example.com";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.length() <= 1) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "URL parameter is required.");
            return;
        }
        
        String url = pathInfo.substring(1);
        if (redirectInvalidUrl(url, response)) {
            response.sendRedirect(url);
        }
    }

    private boolean redirectInvalidUrl(String url, HttpServletResponse response) throws IOException {
        if (url.contains(ALLOWED_DOMAIN)) {
            return true;
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "URL is not allowed.");
            return false;
        }
    }
}