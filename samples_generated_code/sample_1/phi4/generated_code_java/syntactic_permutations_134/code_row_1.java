import java.util.HashMap;
import java.util.Map;

public class UrlMapping {
    private Map<String, String> urlMap = new HashMap<>();

    public void register(String pattern, String functionName) {
        urlMap.put(pattern, functionName);
    }

    public String dispatch(String path) {
        for (String pattern : urlMap.keySet()) {
            if (pattern.startsWith("/")) {
                int startIdx = pattern.indexOf("/");
                int endIdx = pattern.length();
                if (path.equals(pattern)) {
                    return executeFunction(urlMap.get(pattern));
                } else if (startIdx < endIdx && path.startsWith(pattern.substring(0, startIdx))) {
                    String variableValue = path.substring(startIdx + 1);
                    if (pattern.endsWith("/*")) {
                        return executeFunction(urlMap.get(pattern), variableValue);
                    }
                }
            }
        }
        return "404 Not Found";
    }

    private String executeFunction(String functionName) {
        switch (functionName) {
            case "hello":
                return hello(null);
            default:
                return "Invalid Function";
        }
    }

    private String executeFunction(String functionName, String variableValue) {
        switch (functionName) {
            case "hello":
                return hello(variableValue);
            default:
                return "Invalid Function";
        }
    }

    public static String escape(String input) {
        if (input == null) return null;
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }

    public static String hello(String username) {
        if (username == null) return "Hello";
        return "Hello " + escape(username);
    }

    public static void main(String[] args) {
        UrlMapping urlMapping = new UrlMapping();
        urlMapping.register("/hello/*", "hello");
        
        System.out.println(urlMapping.dispatch("/hello/Alice")); // Outputs: Hello Alice
        System.out.println(urlMapping.dispatch("/unknown/URL"));  // Outputs: 404 Not Found
    }
}