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
