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
        String url = request.getPathInfo();
        if (url == null || !url.startsWith("/")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
            return;
        }

        url = url.substring(1); // Remove leading slash

        if (isExampleComURL(url)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "Only example.com URLs are allowed");
        }
    }

    private boolean isExampleComURL(String url) {
        return url.toLowerCase().startsWith("http://example.com/") || url.toLowerCase().startsWith("https://example.com/");
    }
}