import java.util.HashMap;
import java.util.Map;

public class URLMapping {

    private final Map<String, Function> urlFunctionMap = new HashMap<>();

    public URLMapping() {
        // Registering the function for the /hello/{username} URL pattern.
        registerFunction("/hello/", this::handleHello);
    }

    public void registerFunction(String urlPattern, Function handler) {
        urlFunctionMap.put(urlPattern, handler);
    }

    public String handleRequest(String url) {
        for (String pattern : urlFunctionMap.keySet()) {
            if (url.startsWith(pattern)) {
                return urlFunctionMap.get(pattern).execute(url.substring(pattern.length()));
            }
        }
        return "404 Not Found";
    }

    private String handleHello(String username) {
        String escapedUsername = escape(username);
        return "Hello " + escapedUsername;
    }

    private String escape(String input) {
        if (input == null || input.isEmpty()) {
            return input;
        }
        StringBuilder sb = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '&':
                    sb.append("&amp;");
                    break;
                case '<':
                    sb.append("&lt;");
                    break;
                case '>':
                    sb.append("&gt;");
                    break;
                case '"':
                    sb.append("&quot;");
                    break;
                case '\'':
                    sb.append("&#x27;");
                    break;
                default:
                    sb.append(c);
            }
        }
        return sb.toString();
    }

    @FunctionalInterface
    private interface Function {
        String execute(String parameter);
    }

    public static void main(String[] args) {
        URLMapping urlMapping = new URLMapping();

        // Simulating a request to the /hello/username URL.
        String response = urlMapping.handleRequest("/hello/JaneDoe");
        System.out.println(response);  // Output: Hello JaneDoe

        // Simulating another request with special characters in username.
        response = urlMapping.handleRequest("/hello/<Jane>");
        System.out.println(response);  // Output: Hello &lt;Jane&gt;
    }
}