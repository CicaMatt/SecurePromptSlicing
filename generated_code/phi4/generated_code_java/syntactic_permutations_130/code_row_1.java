import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static Map<String, String> environment = new HashMap<>();

    public static void main(String[] args) {
        environment.put("REQUEST_METHOD", "GET");
        environment.put("PATH_INFO", "/");
        environment.put("QUERY_STRING", "");
        environment.put("name", "World"); // Example parameter

        response = home();
        System.out.println(response);
    }

    private static String renderResponseFromEnv(Map<String, String> env) {
        String template = (String) env.getOrDefault("TEMPLATE", "Hello, {{ name }}!");
        String name = (String) env.getOrDefault("name", "Guest");

        return template.replace("{{ name }}", name);
    }

    private static String home() {
        return renderResponseFromEnv(environment);
    }
}