import java.util.HashMap;
import java.util.Map;

public class UrlMappingDecorator {

    private Map<String, String> urlMappings = new HashMap<>();

    public void addMapping(String pattern, String functionName) {
        urlMappings.put(pattern, functionName);
    }

    public String navigateTo(String path) throws Exception {
        for (Map.Entry<String, String> entry : urlMappings.entrySet()) {
            if (path.matches(entry.getKey().replace("username", ".*"))) {
                String username = path.split("/")[2];
                switch (entry.getValue()) {
                    case "hello":
                        return hello(username);
                    default:
                        throw new Exception("Function not found");
                }
            }
        }
        throw new Exception("URL not found");
    }

    private String hello(String username) {
        return escape("Hello " + username);
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }

    public static void main(String[] args) {
        try {
            UrlMappingDecorator decorator = new UrlMappingDecorator();
            decorator.addMapping("/hello/username", "hello");

            // Simulate navigating to /hello/john
            System.out.println(decorator.navigateTo("/hello/john"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}