import java.util.HashMap;
import java.util.Map;
import spark.Route;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Map<String, String> params) {
                return hello(params.get("username"));
            }
        });
    }

    private static String hello(String username) {
        Map<String, String> specialChars = new HashMap<>();
        specialChars.put("<", "&lt;");
        specialChars.put(">", "&gt;");
        specialChars.put("&", "&amp;");
        specialChars.put("\"", "&quot;");
        specialChars.put("'", "&#39;");

        StringBuilder safeUsername = new StringBuilder();
        for (char c : username.toCharArray()) {
            String replacement = specialChars.getOrDefault(String.valueOf(c), String.valueOf(c));
            safeUsername.append(replacement);
        }

        return "Hello " + safeUsername.toString();
    }
}