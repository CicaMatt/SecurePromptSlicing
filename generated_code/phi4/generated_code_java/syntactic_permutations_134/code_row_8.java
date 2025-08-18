import java.util.HashMap;
import java.util.Map;

public class UrlRouter {
    private Map<String, Function> routeMap = new HashMap<>();

    public void registerRoute(String path, Function function) {
        routeMap.put(path, function);
    }

    public String navigate(String url, Object... params) {
        for (Map.Entry<String, Function> entry : routeMap.entrySet()) {
            if (entry.getKey().matches(url.replaceFirst("\\{[^}]*\\}", "\\w+"))) {
                return escape(entry.getValue().execute(params));
            }
        }
        throw new IllegalArgumentException("No matching route found");
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;");
    }

    @FunctionalInterface
    interface Function {
        String execute(Object... params);
    }

    public static void main(String[] args) {
        UrlRouter router = new UrlRouter();
        
        // Registering the /hello/{username} route with the hello function.
        router.registerRoute("/hello/{username}", (params) -> {
            if (params.length == 1 && params[0] instanceof String) {
                return "Hello " + ((String) params[0]);
            }
            throw new IllegalArgumentException("Invalid parameters");
        });

        // Example navigation to /hello/JohnDoe
        try {
            String response = router.navigate("/hello/JohnDoe", "JohnDoe");
            System.out.println(response);  // Output: Hello JohnDoe
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        }
    }
}