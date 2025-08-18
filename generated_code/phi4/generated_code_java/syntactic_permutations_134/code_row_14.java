import java.util.HashMap;
import java.util.Map;

public class UrlMapping {

    private static Map<String, String> urlMap = new HashMap<>();

    public static void main(String[] args) {
        initializeUrlMapping();
        
        // Simulate accessing different URLs
        System.out.println(handleRequest("/hello/JohnDoe"));
        System.out.println(handleRequest("/hello/Jane_Doe"));
    }

    private static void initializeUrlMapping() {
        urlMap.put("/hello/", "com.example.UrlMapping::sayHello");
    }

    private static String handleRequest(String path) {
        for (String key : urlMap.keySet()) {
            if (path.startsWith(key)) {
                String handler = urlMap.get(key);
                try {
                    // Extract the username from the URL
                    int startIdx = key.length();
                    String username = path.substring(startIdx);

                    // Get the method reference and invoke it dynamically
                    String[] parts = handler.split("::");
                    Class<?> clazz = Class.forName(parts[0]);
                    java.lang.reflect.Method method = clazz.getDeclaredMethod(parts[1], String.class);
                    
                    return (String) method.invoke(clazz.newInstance(), escape(username));
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return "404 Not Found";
    }

    public static String sayHello(String username) {
        return "Hello, " + username;
    }

    private static String escape(String input) {
        if (input == null) {
            return null;
        }
        StringBuilder escaped = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    escaped.append("&lt;");
                    break;
                case '>':
                    escaped.append("&gt;");
                    break;
                case '&':
                    escaped.append("&amp;");
                    break;
                case '"':
                    escaped.append("&quot;");
                    break;
                default:
                    escaped.append(c);
            }
        }
        return escaped.toString();
    }
}