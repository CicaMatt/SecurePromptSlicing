import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, String> env = Map.of(
            "REQUEST_METHOD", "GET",
            "PATH_INFO", "/home",
            "QUERY_STRING", ""
        );

        System.out.println(home(env));
    }

    public static String renderResponseFromEnv(Map<String, String> environment) {
        String name = environment.getOrDefault("NAME", "World");
        String template = getTemplate(environment);
        String renderedTemplate = renderTemplate(template, name);
        return createResponse(renderedTemplate);
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    private static String getTemplate(Map<String, String> environment) {
        // In a real application, this would load the template from a file or other resource.
        return "Hello, %s!";
    }

    private static String renderTemplate(String template, String name) {
        return String.format(template, name);
    }

    private static String createResponse(String content) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n" + content;
    }
}