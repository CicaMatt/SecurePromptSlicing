import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");

        StringWriter writer = new StringWriter();
        writer.write("<html><body>");
        writer.write("<h1>Hello, " + name + "!</h1>");
        writer.write("</body></html>");

        return writer.toString();
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> request = new HashMap<>();
        request.put("name", "World");

        Map<String, Object> env = new HashMap<>();
        env.put("request", request);

        String response = home(env);
        System.out.println(response);
    }
}