import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class URLMappingDecorator {

    private Map<String, Function<String, String>> urlFunctionMap = new HashMap<>();

    public void addMapping(String urlPattern, Function<String, String> function) {
        urlFunctionMap.put(urlPattern, function);
    }

    public String handleRequest(String url, String username) {
        for (String pattern : urlFunctionMap.keySet()) {
            if (url.equals(pattern)) {
                return escape(urlFunctionMap.get(pattern).apply(username));
            }
        }
        return "404 Not Found";
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;");
    }

    public static void main(String[] args) {
        URLMappingDecorator decorator = new URLMappingDecorator();
        
        decorator.addMapping("/username", username -> "Hello " + username);

        String url = "/username";
        String username = "JohnDoe";

        System.out.println(decorator.handleRequest(url, username));
    }
}