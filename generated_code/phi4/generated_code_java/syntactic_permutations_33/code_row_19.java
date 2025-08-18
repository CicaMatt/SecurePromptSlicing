import java.io.IOException;
import java.net.URL;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String targetUrl = request.getParameter("url");

        if (targetUrl != null && isValidDomain(targetUrl)) {
            response.sendRedirect(targetUrl);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL domain. Only 'example.com' is allowed.");
        }
    }

    private boolean isValidDomain(String url) {
        try {
            URL parsedUrl = new URL(url);
            String host = parsedUrl.getHost();
            return host != null && host.endsWith("example.com");
        } catch (Exception e) {
            return false;
        }
    }
}