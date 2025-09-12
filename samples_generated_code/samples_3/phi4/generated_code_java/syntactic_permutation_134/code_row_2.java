import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class URLFunctionMapper {

    private Map<String, Function<String, String>> urlMap = new HashMap<>();

    public void register(String path, Function<String, String> function) {
        urlMap.put(path, function);
    }

    public String execute(String path, String username) {
        if (urlMap.containsKey(path)) {
            return escape(urlMap.get(path).apply(username));
        }
        return "404 Not Found";
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static void main(String[] args) {
        URLFunctionMapper mapper = new URLFunctionMapper();
        mapper.register("/hello", URLFunctionMapper::hello);

        // Example usage
        System.out.println(mapper.execute("/hello", "Alice"));
    }
}