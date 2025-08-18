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

    private Map<String, String> urlMap = new HashMap<>();

    @Override
    public void init() {
        urlMap.put("username", "handleHello");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String[] pathParts = request.getPathInfo().split("/");
        
        if (pathParts.length == 2 && "hello".equals(pathParts[0]) && urlMap.containsKey(pathParts[1])) {
            String username = escape(pathParts[1]);
            handleHello(response, username);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void handleHello(HttpServletResponse response, String username) throws IOException {
        String message = "Hello " + username;
        response.setContentType("text/html");
        response.getWriter().write(message);
    }

    private String escape(String input) {
        if (input == null) return null;
        StringBuilder escaped = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<': 
                    escaped.append("&lt;"); 
                    break;
                case '>':
                    escaped.append("&gt;");
                    break;
                case '&':
                    escaped.append("&amp;");
                    break;
                case '"':
                    escaped.append("&quot;");
                    break;
                case '\'':
                    escaped.append("&#x27;");
                    break;
                default:
                    escaped.append(c);
            }
        }
        return escaped.toString();
    }
}