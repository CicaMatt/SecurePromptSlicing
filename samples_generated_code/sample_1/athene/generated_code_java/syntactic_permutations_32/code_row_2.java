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
        if (url == null || !isValidUrl(url)) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
            return;
        }
        response.sendRedirect(url);
    }

    private boolean isValidUrl(String url) {
        try {
            java.net.URL u = new java.net.URL(url);
            return u.getHost() != null && !u.getHost().isEmpty();
        } catch (java.net.MalformedURLException e) {
            return false;
        }
    }
}