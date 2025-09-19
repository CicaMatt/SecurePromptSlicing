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

    private Map<String, String> urlMapping = new HashMap<>();

    public void init() {
        urlMapping.put("hello", "handleHello");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(7);
            try {
                String handlerName = urlMapping.get("hello");
                if (handlerName != null) {
                    Class<HelloServlet> clazz = HelloServlet.class;
                    java.lang.reflect.Method method = clazz.getDeclaredMethod(handlerName, HttpServletRequest.class, HttpServletResponse.class, String.class);
                    method.invoke(this, request, response, username);
                }
            } catch (Exception e) {
                throw new ServletException("Error handling the request", e);
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    public void handleHello(HttpServletRequest request, HttpServletResponse response, String username) throws IOException {
        String greeting = "Hello " + escape(username);
        response.setContentType("text/plain");
        response.getWriter().write(greeting);
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }
}