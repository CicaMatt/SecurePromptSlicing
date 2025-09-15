import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        
        if (pathInfo != null && !pathInfo.isEmpty()) {
            String urlToRedirect = pathInfo.substring(1);
            
            try {
                redirectInvalidUrl(response, urlToRedirect);
            } catch (Exception e) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL: " + urlToRedirect);
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No URL provided");
        }
    }

    private void redirectInvalidUrl(HttpServletResponse response, String urlString) throws IOException {
        if (isValidHttpUrl(urlString)) {
            response.sendRedirect(urlString);
        } else {
            throw new IllegalArgumentException("Invalid URL format");
        }
    }

    private boolean isValidHttpUrl(String url) {
        return url.startsWith("http://") || url.startsWith("https://");
    }
}
