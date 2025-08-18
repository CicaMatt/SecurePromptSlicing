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
        String url = request.getPathInfo().substring(1);
        if (isAllowedDomain(url)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL domain");
        }
    }

    private boolean isAllowedDomain(String url) {
        try {
            java.net.URL netUrl = new java.net.URL(url);
            return ALLOWED_DOMAIN.equals(netUrl.getHost());
        } catch (java.net.MalformedURLException e) {
            return false;
        }
    }
}