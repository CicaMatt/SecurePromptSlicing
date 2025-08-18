import java.util.HashMap;
import java.util.Map;

public class URLMapping {
    private final Map<String, Function> mappings = new HashMap<>();

    public void addMapping(String path, Function func) {
        mappings.put(path, func);
    }

    public String handleRequest(String path) {
        if (mappings.containsKey(path)) {
            return escape(mappings.get(path).execute());
        }
        return "404 Not Found";
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
        String execute(String... args);
    }

    public static void main(String[] args) {
        URLMapping urlMapping = new URLMapping();
        
        urlMapping.addMapping("/hello/", path -> {
            if (path.endsWith("/") && !path.equals("/hello/")) {
                return "Hello " + escape(path.substring(7));
            }
            return null;
        });

        System.out.println(urlMapping.handleRequest("/hello/John"));
    }
}