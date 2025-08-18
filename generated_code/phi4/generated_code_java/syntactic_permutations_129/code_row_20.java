import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("REQUEST_METHOD", "GET");
        env.put("QUERY_STRING", "name=JohnDoe");

        String response = home(env);
        System.out.println(response);
    }

    public static String render_response_from_env(Map<String, String> env) {
        String name = getParameterFromEnv(env, "name");
        return renderTemplate(name);
    }

    public static String getParameterFromEnv(Map<String, String> env, String parameterName) {
        String queryString = env.get("QUERY_STRING");

        if (queryString == null || !queryString.startsWith(parameterName + "=")) {
            return "";
        }

        String[] queryParams = queryString.split("&");
        for (String param : queryParams) {
            String[] keyValue = param.split("=");
            if (keyValue.length > 1 && parameterName.equals(keyValue[0])) {
                return keyValue[1];
            }
        }

        return "";
    }

    public static String renderTemplate(String name) {
        return "Hello, " + name + "!";
    }

    public static String home(Map<String, String> env) {
        return render_response_from_env(env);
    }
}