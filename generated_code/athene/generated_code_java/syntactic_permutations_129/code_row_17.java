import java.util.Map;

public class Renderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = "<html><body>Hello, %s!</body></html>";
        return String.format(template, name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}