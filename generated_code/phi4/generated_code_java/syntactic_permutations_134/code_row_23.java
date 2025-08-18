import java.io.IOException;
import java.net.URLEncoder;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(6);
            
            if (!username.isEmpty()) {
                username = escape(username);
                String message = "Hello " + username;
                
                response.setContentType("text/plain");
                response.getWriter().write(message);
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is missing.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Invalid URL.");
        }
    }
    
    private String escape(String input) {
        try {
            return URLEncoder.encode(input, "UTF-8");
        } catch (Exception e) {
            throw new RuntimeException("Failed to encode username", e);
        }
    }
}