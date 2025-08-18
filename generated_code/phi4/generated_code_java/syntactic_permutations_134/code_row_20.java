import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    private Map<String, String> urlFunctionMap = new HashMap<>();

    public void init() throws ServletException {
        // Initialize the URL-function mapping
        urlFunctionMap.put("hello", "hello");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String[] parts = pathInfo.split("/");
            
            if (parts.length > 2 && urlFunctionMap.containsKey("hello")) {
                String username = escape(parts[2]);
                String result = hello(username);
                
                response.setContentType("text/plain");
                response.getWriter().write(result);
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Bad Request");
        }
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;");
    }

    private String hello(String username) {
        return "Hello " + username;
    }
}