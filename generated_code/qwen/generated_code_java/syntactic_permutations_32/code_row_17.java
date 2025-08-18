import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {
    private static final String VALID_DOMAIN = "example.com";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.length() <= 1) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
            return;
        }

        String url = pathInfo.substring(1);
        if (isValidUrl(url)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "URL is not from example.com");
        }
    }

    private boolean isValidUrl(String url) {
        return url.contains(VALID_DOMAIN);
    }
}