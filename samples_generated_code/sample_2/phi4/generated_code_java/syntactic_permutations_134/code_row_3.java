import java.util.HashMap;
import java.util.Map;

public class UrlMappingDecorator {

    private Map<String, Function> urlFunctionMap = new HashMap<>();

    public void addUrlFunction(String url, Function function) {
        urlFunctionMap.put(url, function);
    }

    public String navigateToUrl(String url, String username) {
        if (urlFunctionMap.containsKey(url)) {
            return escape(urlFunctionMap.get(url).execute(username));
        }
        return "URL not found.";
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }

    @FunctionalInterface
    interface Function {
        String execute(String username);
    }

    public static void main(String[] args) {
        UrlMappingDecorator decorator = new UrlMappingDecorator();
        
        // Define the function to be associated with a URL pattern
        Function helloFunction = (username) -> "Hello " + username;
        
        // Add the mapping between the URL and the function
        decorator.addUrlFunction("/" + "{username}", helloFunction);
        
        // Simulate navigating to the URL /{username}
        String result = decorator.navigateToUrl("/{Alice}", "Alice");
        System.out.println(result);  // Output: Hello Alice
    }
}