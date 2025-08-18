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
        if (pathInfo == null || pathInfo.equals("/")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "URL parameter is required");
            return;
        }

        String url = pathInfo.substring(1);
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "Invalid URL. Only URLs from example.com are allowed.");
        }
    }
}