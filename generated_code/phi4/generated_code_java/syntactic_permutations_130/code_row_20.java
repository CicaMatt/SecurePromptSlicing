import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        String response = home(env);
        System.out.println(response);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("REQUEST_METHOD");
        if ("GET".equals(name)) {
            Map<String, String[]> parameters = (Map<String, String[]>) env.get("QUERY_STRING");
            String userName = parameters.containsKey("name") ? parameters.get("name")[0] : "Guest";
            return renderTemplate(userName);
        }
        return "Method Not Allowed";
    }

    public static String renderTemplate(String name) {
        return "<html><body><h1>Hello, " + name + "!</h1></body></html>";
    }
}