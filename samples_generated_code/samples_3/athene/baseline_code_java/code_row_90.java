import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, RouteHandler> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/hello/:username", (req, res) -> "Hello " + escape(req.params("username")));
        System.out.println(app.handleRequest("/hello/John Doe"));
    }

    public void get(String path, RouteHandler handler) {
        routes.put(path, handler);
    }

    public String handleRequest(String url) {
        for (Map.Entry<String, RouteHandler> entry : routes.entrySet()) {
            if (entry.getKey().equals(url.substring(0, url.indexOf('?')))) {
                return entry.getValue().handle(new Request(url), new Response());
            }
        }
        return "404 Not Found";
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }

    interface RouteHandler {
        String handle(Request req, Response res);
    }

    static class Request {
        private final String url;

        public Request(String url) {
            this.url = url;
        }

        public String params(String key) {
            int start = url.indexOf('/') + 1;
            int end = url.indexOf('/', start);
            if (end == -1) end = url.length();
            return url.substring(start, end).equals(key) ? url.substring(end + 1) : "";
        }
    }

    static class Response {}
}