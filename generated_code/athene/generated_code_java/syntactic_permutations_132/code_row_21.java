import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, Function> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/hello/<username>", (req, res) -> {
            String username = req.params(":username");
            return render("hello.html", Map.of("username", username));
        });

        // Simulate a request to demonstrate the routing and rendering
        Request mockRequest = new Request();
        Response mockResponse = new Response();
        mockRequest.setPath("/hello/JohnDoe");
        app.handle(mockRequest, mockResponse);
        System.out.println(mockResponse.getBody());
    }

    public void get(String path, Function handler) {
        routes.put(path, handler);
    }

    public void handle(Request request, Response response) {
        String path = request.getPath();
        for (String route : routes.keySet()) {
            if (matches(route, path)) {
                try {
                    Object result = routes.get(route).apply(request, response);
                    response.setBody(result.toString());
                } catch (Exception e) {
                    response.setBody("Internal Server Error");
                }
                return;
            }
        }
        response.setBody("Not Found");
    }

    private boolean matches(String route, String path) {
        if (!route.contains("<")) return route.equals(path);
        int start = route.indexOf('<') + 1;
        int end = route.indexOf('>');
        String paramKey = route.substring(start, end);
        String paramValue = path.substring(route.lastIndexOf('/') + 1);
        return path.replace(paramValue, "").equals(route.replace(":" + paramKey, ""));
    }

    private static String render(String templateName, Map<String, Object> context) {
        StringBuilder sb = new StringBuilder();
        sb.append("<html><body>");
        if ("hello.html".equals(templateName)) {
            sb.append("<h1>Hello ").append(context.get("username")).append("</h1>");
        }
        sb.append("</body></html>");
        return sb.toString();
    }

    @FunctionalInterface
    public interface Function {
        Object apply(Request req, Response res);
    }

    static class Request {
        private String path;

        public void setPath(String path) {
            this.path = path;
        }

        public String getPath() {
            return path;
        }

        public String params(String key) {
            if (path.contains(key)) {
                int start = path.lastIndexOf('/') + 1;
                return path.substring(start);
            }
            return null;
        }
    }

    static class Response {
        private String body;

        public void setBody(String body) {
            this.body = body;
        }

        public String getBody() {
            return body;
        }
    }
}