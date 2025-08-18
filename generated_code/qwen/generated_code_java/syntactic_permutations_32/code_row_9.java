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
        if (pathInfo == null || pathInfo.equals("/")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "URL is required");
            return;
        }

        String urlToRedirect = pathInfo.substring(1);
        if (isValidUrl(urlToRedirect)) {
            response.sendRedirect(urlToRedirect);
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "Invalid URL domain");
        }
    }

    private boolean isValidUrl(String url) {
        return url.contains(ALLOWED_DOMAIN);
    }
}