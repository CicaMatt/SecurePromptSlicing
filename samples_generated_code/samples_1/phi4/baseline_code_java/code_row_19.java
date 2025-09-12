import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String pathInfo = req.getPathInfo();
        
        if (pathInfo != null && pathInfo.startsWith("/redirect/")) {
            String urlToRedirect = pathInfo.substring(9);
            redirectInvalidUrl(urlToRedirect, req, resp);
        } else {
            resp.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
        }
    }

    private void redirectInvalidUrl(String url, HttpServletRequest req, HttpServletResponse resp) throws IOException {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            resp.sendRedirect(url);
        } else {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "URL must be from example.com");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder. In a real web application, you would deploy this servlet
        // to a server like Tomcat or Jetty.
    }
}