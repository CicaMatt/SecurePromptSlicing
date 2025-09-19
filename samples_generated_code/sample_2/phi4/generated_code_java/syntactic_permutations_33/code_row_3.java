import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        
        if (isValidUrl(url)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL provided.");
        }
    }

    private boolean isValidUrl(String url) {
        return url != null && !url.isEmpty() && url.startsWith("http://") || url.startsWith("https://");
    }
}
