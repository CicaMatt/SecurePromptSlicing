import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.length() < 2) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
            return;
        }

        String url = pathInfo.substring(1);
        if (redirect_invalid_url(url)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "URL must be from example.com");
        }
    }

    private boolean redirect_invalid_url(String url) {
        return url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com");
    }
}