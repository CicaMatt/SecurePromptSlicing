import java.util.HashMap;
import java.util.Map;

public class UrlMappingDecorator {

    private Map<String, String> mappings = new HashMap<>();

    public void addMapping(String urlPattern, String functionName) {
        mappings.put(urlPattern, functionName);
    }

    public String handleRequest(String requestUrl) {
        for (Map.Entry<String, String> entry : mappings.entrySet()) {
            if (requestUrl.matches(entry.getKey().replace("username", "([\\w]+)"))) {
                String[] parts = requestUrl.split("/");
                String username = parts[parts.length - 1];
                try {
                    return this.getClass().getMethod(entry.getValue(), String.class).invoke(this, username);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return "Not Found";
    }

    public String hello(String username) {
        return escape("Hello " + username);
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }

    public static void main(String[] args) {
        UrlMappingDecorator decorator = new UrlMappingDecorator();
        decorator.addMapping("/hello/username", "hello");

        String response1 = decorator.handleRequest("/hello/johndoe");
        System.out.println(response1);

        String response2 = decorator.handleRequest("/unknown/path");
        System.out.println(response2);
    }
}