import java.util.HashMap;
import java.util.function.Function;

public class UrlMappingDecorator {
    private final HashMap<String, Function<String, String>> urlFunctionMap = new HashMap<>();

    public void addUrlMapping(String urlPattern, Function<String, String> function) {
        urlFunctionMap.put(urlPattern, function);
    }

    public String navigateToUrl(String url, String username) {
        if (url.startsWith("/")) {
            String key = url.substring(1);
            if (urlFunctionMap.containsKey(key)) {
                return escape(urlFunctionMap.get(key).apply(username));
            }
        }
        return "URL not found";
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }

    public static void main(String[] args) {
        UrlMappingDecorator decorator = new UrlMappingDecorator();

        // Add mapping for the URL pattern "/username"
        decorator.addUrlMapping("username", username -> "Hello " + username);

        // Simulating user navigating to "/username" with a specific username
        String result = decorator.navigateToUrl("/username", "JohnDoe");
        
        System.out.println(result);  // Output: Hello JohnDoe
    }
}