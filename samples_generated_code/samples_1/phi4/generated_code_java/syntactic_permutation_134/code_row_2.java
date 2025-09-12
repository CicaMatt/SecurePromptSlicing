import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class UrlMappingExample {

    private static Map<String, Function<String, String>> urlFunctionMap = new HashMap<>();

    public static void main(String[] args) {
        setupUrlMappings();

        // Simulate URL navigation
        String response = navigateTo("/hello/john");
        System.out.println(response);
    }

    private static void setupUrlMappings() {
        urlFunctionMap.put("/hello/", UrlMappingExample::createHelloResponse);
    }

    private static String navigateTo(String url) {
        String key = extractKey(url);
        Function<String, String> function = urlFunctionMap.get(key);
        if (function != null) {
            String username = url.replaceFirst(".*?/([^/?]+)", "$1");
            return escape(function.apply(username));
        }
        return "404 Not Found";
    }

    private static String extractKey(String url) {
        int slashIndex = url.indexOf('/');
        return slashIndex == -1 ? "" : url.substring(0, slashIndex + 1);
    }

    private static String createHelloResponse(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        if (input == null) {
            return "";
        }
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }
}