import java.util.HashMap;
import java.util.Map;

public class URLDecorator {

    private Map<String, Runnable> urlFunctionMap = new HashMap<>();

    public void registerUrl(String urlTemplate, Runnable action) {
        String key = urlTemplate.replace("username", "%s");
        urlFunctionMap.put(key, action);
    }

    public String navigateToUrl(String username) {
        for (String key : urlFunctionMap.keySet()) {
            if (key.matches("%s")) {
                Runnable action = urlFunctionMap.get(key);
                StringBuilder result = new StringBuilder();
                appendActionResult(result, action, username);
                return escapeHtml(result.toString());
            }
        }
        throw new IllegalArgumentException("URL not registered");
    }

    private void appendActionResult(StringBuilder sb, Runnable action, String username) {
        if (action != null) {
            sb.append("Hello ").append(username);
        }
    }

    public static String escapeHtml(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#x27;")
                   .replace("/", "&#x2F;");
    }

    public static void main(String[] args) {
        URLDecorator decorator = new URLDecorator();
        decorator.registerUrl("/username", () -> System.out.println("Function executed"));

        String username = "JohnDoe";
        String result = decorator.navigateToUrl(username);
        System.out.println(result);  // Output: Hello JohnDoe
    }
}