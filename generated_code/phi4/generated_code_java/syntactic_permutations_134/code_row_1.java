import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloDecorator {

    private Map<String, String> urlMappings = new HashMap<>();

    public HelloDecorator() {
        urlMappings.put("/hello/", this::handleHello);
    }

    public void service(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String path = request.getPathInfo();
        if (path != null && urlMappings.containsKey(path)) {
            urlMappings.get(path).run(request, response);
        } else {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void handleHello(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String username = request.getParameter("username");
        if (username == null || username.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }
        String message = "Hello " + escape(username);
        response.setContentType("text/plain");
        response.getWriter().write(message);
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