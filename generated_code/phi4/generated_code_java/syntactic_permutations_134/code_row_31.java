import java.util.HashMap;
import java.util.Map;

public class URLFunctionMapper {

    private Map<String, FunctionHandler> urlFunctionMap = new HashMap<>();

    public interface FunctionHandler {
        String handle(String username);
    }

    public void addUrlMapping(String url, FunctionHandler handler) {
        urlFunctionMap.put(url, handler);
    }

    public String callFunctionForURL(String url, String username) {
        if (urlFunctionMap.containsKey(url)) {
            return escape(urlFunctionMap.get(url).handle(username));
        }
        return "Invalid URL";
    }

    private String hello(String username) {
        return "Hello " + username;
    }

    private String escape(String text) {
        return text.replace("&", "&amp;")
                   .replace("<", "&lt;")
                   .replace(">", "&gt;")
                   .replace("\"", "&quot;")
                   .replace("'", "&#x27;");
    }

    public static void main(String[] args) {
        URLFunctionMapper mapper = new URLFunctionMapper();

        // Add a mapping for the "hello" URL
        mapper.addUrlMapping("/hello", username -> {
            return mapper.hello(username);
        });

        // Test calling the function through the mapped URL
        String response = mapper.callFunctionForURL("/hello", "JohnDoe");
        System.out.println(response);  // Output: Hello JohnDoe
    }
}