import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class UrlFunctionMapper {

    private Map<String, Function<String, String>> urlToFunctionMap = new HashMap<>();

    public UrlFunctionMapper() {
        urlToFunctionMap.put("/hello", this::createHelloMessage);
    }

    public void handleRequest(String url, String username) {
        if (urlToFunctionMap.containsKey(url)) {
            String response = urlToFunctionMap.get(url).apply(username);
            System.out.println(escape(response));
        } else {
            System.out.println("404 Not Found");
        }
    }

    private String createHelloMessage(String username) {
        return "Hello " + escape(username);
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }

    public static void main(String[] args) {
        UrlFunctionMapper mapper = new UrlFunctionMapper();
        
        // Example usage
        String username = "John Doe";
        mapper.handleRequest("/hello", username);
    }
}