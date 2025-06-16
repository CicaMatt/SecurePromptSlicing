import java.io.IOException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class Redirect extends HttpServlet {
    private String url;

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException {
        // Get the URL parameter
        url = request.getParameter("url");
        if (redirect_invalid_url()) {
            response.sendRedirect(url);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Invalid URL: " + url);
        }
    }

    // Check if the URL is from example.com
    public boolean redirect_invalid_url() {
        return url.startsWith("https://example.com/");
    }
}