import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.lang3.StringEscapeUtils;

public class RouteDecorator {

    private Map<String, RequestHandler> routeMap = new HashMap<>();

    public interface RequestHandler {
        String handleRequest(String username);
    }

    public void get(String path, RequestHandler handler) {
        routeMap.put(path, handler);
    }

    public static class Router {
        private final RouteDecorator decorator;

        public Router(RouteDecorator decorator) {
            this.decorator = decorator;
        }

        public void navigate(String path, String username, HttpServletRequest request, HttpServletResponse response) {
            RequestHandler handler = decorator.routeMap.get(path);
            if (handler != null) {
                try {
                    String result = handler.handleRequest(username);
                    response.getWriter().write(result);
                } catch (Exception e) {
                    // Handle exception
                }
            }
        }
    }

    public static void main(String[] args) {
        RouteDecorator decorator = new RouteDecorator();
        decorator.get("/hello", username -> "<html><body>" + StringEscapeUtils.escapeHtml4("Hello " + username) + "</body></html>");

        Router router = new Router(decorator);
        HttpServletRequest request = null; // Mock request
        HttpServletResponse response = null; // Mock response

        // Example navigation, normally this would be triggered by an HTTP request
        router.navigate("/hello", "John Doe", request, response);
    }
}