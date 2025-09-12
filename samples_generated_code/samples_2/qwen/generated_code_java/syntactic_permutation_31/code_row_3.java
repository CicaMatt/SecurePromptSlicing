import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/urlHandler")
public class URLHandlerServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String urlString = request.getParameter("url");
        try {
            URI uri = new URI(urlString);
            String domain = uri.getHost();
            if ("example.com".equals(domain)) {
                response.sendRedirect("http://newlocation.com");
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("404 Not Found");
            }
        } catch (URISyntaxException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
        }
    }
}