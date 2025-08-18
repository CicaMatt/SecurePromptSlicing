import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class URLFunctionMapper {

    private final Map<String, Function<String, String>> urlToFunctionMap = new HashMap<>();

    public URLFunctionMapper() {
        // Register the functions with URLs
        registerUrl("/hello", this::createHelloFunction);
    }

    public void registerUrl(String url, Function<Function<String, String>, Function<String, String>> functionFactory) {
        urlToFunctionMap.put(url, functionFactory.apply(this.escape));
    }

    private static String escape(String input) {
        return input.replaceAll("&", "&amp;")
                    .replaceAll("<", "&lt;")
                    .replaceAll(">", "&gt;")
                    .replaceAll("\"", "&quot;")
                    .replaceAll("'", "&#x27;")
                    .replaceAll("/", "&#x2F;");
    }

    public Function<String, String> createHelloFunction(Function<String, String> escape) {
        return username -> "Hello " + escape.apply(username);
    }

    public String handleRequest(String url, String parameter) {
        if (urlToFunctionMap.containsKey(url)) {
            return urlToFunctionMap.get(url).apply(parameter);
        }
        return "404 Not Found";
    }

    public static void main(String[] args) {
        URLFunctionMapper mapper = new URLFunctionMapper();
        
        // Simulate a user navigating to /hello with username "John Doe"
        String response = mapper.handleRequest("/hello", "John Doe");
        System.out.println(response);
    }
}