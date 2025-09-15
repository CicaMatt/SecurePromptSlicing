import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        
        if (pathInfo == null || !pathInfo.startsWith("/redirect/")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }
        
        // Extract the URL from the path
        String urlString = pathInfo.substring(10); // Remove "/redirect/"
        redirectInvalidUrl(urlString, request, response);
    }

    private void redirectInvalidUrl(String url, HttpServletRequest request, HttpServletResponse response) throws IOException {
        try {
            new java.net.URL(url).toURI();
            response.sendRedirect(url);
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
        }
    }
}
