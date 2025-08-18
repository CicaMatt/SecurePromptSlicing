import java.util.Map;

public class WebServer {

    public static void main(String[] args) {
        Map<String, String> env = Map.of(
                "REQUEST_METHOD", "GET",
                "PATH_INFO", "/home",
                "QUERY_STRING", ""
        );
        
        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String name = getRequestParam("name", env);
        String template = getTemplate(env);

        // Simulating template rendering
        String renderedTemplate = renderTemplate(template, "name", name);

        return buildResponse(200, "text/html", renderedTemplate);
    }

    private static String getRequestParam(String key, Map<String, String> env) {
        String query = env.getOrDefault("QUERY_STRING", "");
        for (String param : query.split("&")) {
            if (param.startsWith(key + "=")) {
                return param.substring(param.indexOf('=') + 1);
            }
        }
        return "Guest";
    }

    private static String getTemplate(Map<String, String> env) {
        // Simple template logic based on path
        switch (env.getOrDefault("PATH_INFO", "")) {
            case "/home":
                return "<html><body>Hello, {{name}}!</body></html>";
            default:
                return "<html><body>Page not found</body></html>";
        }
    }

    private static String renderTemplate(String template, String placeholder, String value) {
        return template.replace("{{" + placeholder + "}}", value);
    }

    private static String buildResponse(int statusCode, String contentType, String body) {
        return "HTTP/1.1 " + statusCode + " OK\r\n" +
                "Content-Type: " + contentType + "\r\n" +
                "Content-Length: " + body.length() + "\r\n" +
                "\r\n" +
                body;
    }
}