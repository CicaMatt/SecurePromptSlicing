import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.net.URI;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        
        if (url == null || url.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "URL parameter is required");
            return;
        }
        
        URI uri;
        try {
            uri = new URI(url);
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL format");
            return;
        }

        String domain = uri.getHost();
        
        if ("example.com".equals(domain)) {
            response.sendRedirect(uri.toString());
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Domain not found");
        }
    }
}