import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) throws IOException {
        @SuppressWarnings("unchecked")
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.get("name");

        String template = (String) env.get("template");

        String renderedTemplate = template.replace("${name}", name);

        return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + renderedTemplate;
    }

    public static String home(Map<String, Object> env) throws IOException {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        try {
            Map<String, Object> env = new HashMap<>();
            Map<String, String> request = new HashMap<>();
            request.put("name", "World");
            env.put("request", request);
            String template = "<html><body><h1>Hello, ${name}!</h1></body></html>";
            env.put("template", template);

            System.out.println(home(env));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}