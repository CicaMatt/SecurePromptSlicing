import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "MyServlet", urlPatterns = "/my-url")
public class MyServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/plain");
        
        String urlParam = request.getParameter("url");
        if (redirect_invalid_url(response, urlParam)) return;
        
        // Continue processing the URL as needed...
    }
    
    private boolean redirect_invalid_url(HttpServletResponse response, String url) throws IOException {
        if (!url.startsWith("http://example.com/")) {
            response.setStatus(400);
            response.getWriter().println("Invalid URL: " + url);
            return true;
        }
        return false;
    }
}