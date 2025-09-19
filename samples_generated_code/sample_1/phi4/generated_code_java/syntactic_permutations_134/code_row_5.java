import java.util.HashMap;
import java.util.Map;

public class UrlDecorator {

    private static final Map<String, String> urlMap = new HashMap<>();

    public static void main(String[] args) {
        // Example usage
        registerUrlMapping("/hello/", "Hello %s");
        System.out.println(handleRequest("/hello/john_doe"));
    }

    public static void registerUrlMapping(String baseUrl, String format) {
        urlMap.put(baseUrl, format);
    }

    public static String handleRequest(String url) {
        for (String key : urlMap.keySet()) {
            if (url.startsWith(key)) {
                String username = url.substring(key.length());
                return String.format(urlMap.get(key), escape(username));
            }
        }
        return "404 Not Found";
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }
}