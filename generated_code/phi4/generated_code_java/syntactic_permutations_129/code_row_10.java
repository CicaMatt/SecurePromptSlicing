import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final Map<String, String> ENV = new HashMap<>();

    public static void main(String[] args) {
        // Initialize environment for demonstration purposes
        ENV.put("template", "Hello, ${name}!");

        System.out.println(home());
    }

    public static String home() {
        return renderResponseFromEnv(ENV);
    }

    private static String renderResponseFromEnv(Map<String, String> env) {
        String template = env.getOrDefault("template", "Template not found");
        // Simulating a request with some data
        Map<String, String> requestData = new HashMap<>();
        requestData.put("name", "World");

        return render(template, requestData);
    }

    private static String render(String template, Map<String, String> data) {
        for (Map.Entry<String, String> entry : data.entrySet()) {
            template = template.replace("${" + entry.getKey() + "}", entry.getValue());
        }
        return "Response: " + template;
    }
}