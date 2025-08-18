import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class WebApplication {

    public static void main(String[] args) throws Exception {
        Router router = new Router();
        router.get("/hello/:username", new Handler() {
            @Override
            public void handle(HttpServletRequest request, HttpServletResponse response) throws IOException {
                String username = request.getPathInfo().split("/")[2];
                Map<String, Object> model = new HashMap<>();
                model.put("username", username);
                String content = TemplateRenderer.render("hello.html", model);
                response.getWriter().write(content);
            }
        });

        router.start();
    }

    static class Router {
        private Map<String, Handler> routes = new HashMap<>();

        public void get(String path, Handler handler) {
            routes.put(path, handler);
        }

        public void start() throws IOException {
            // Simulate a request for demonstration purposes
            HttpServletRequest request = new MockRequest("/hello/JohnDoe");
            HttpServletResponse response = new MockResponse();
            String path = request.getPathInfo();

            if (routes.containsKey(path)) {
                routes.get(path).handle(request, response);
            } else {
                response.sendError(404, "Not Found");
            }
        }
    }

    interface Handler {
        void handle(HttpServletRequest request, HttpServletResponse response) throws IOException;
    }

    static class TemplateRenderer {
        public static String render(String templateName, Map<String, Object> model) {
            StringBuilder content = new StringBuilder();
            try {
                // Simulate reading from a file
                switch (templateName) {
                    case "hello.html":
                        content.append("Hello, ");
                        content.append(model.get("username"));
                        content.append("!");
                        break;
                    default:
                        content.append("Template not found");
                }
            } catch (Exception e) {
                content.append("Error rendering template: ").append(e.getMessage());
            }
            return content.toString();
        }
    }

    static class MockRequest implements HttpServletRequest {
        private final String pathInfo;

        public MockRequest(String pathInfo) {
            this.pathInfo = pathInfo;
        }

        @Override
        public String getPathInfo() {
            return pathInfo;
        }

        // Implement other methods as needed
    }

    static class MockResponse implements HttpServletResponse {
        @Override
        public void sendError(int sc, String msg) throws IOException {
            System.out.println("HTTP Error " + sc + ": " + msg);
        }

        @Override
        public void sendRedirect(String location) throws IOException {
            // Implement as needed
        }

        @Override
        public void setContentType(String type) {
            // Implement as needed
        }

        @Override
        public java.io.PrintWriter getWriter() throws IOException {
            return new java.io.PrintWriter(System.out);
        }

        // Implement other methods as needed
    }
}