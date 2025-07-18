import java.util.HashMap;
import java.util.Map;
import java.lang.*;
public class UrlMapping {
    Map<String, String> mappings = new HashMap<>();
    public void addURL(String url) {
        String username = "Hello";
        mappings.put(url, escape(username));
    }
    
    private String escape(String text) {
        // convert special characters to HTML-safe sequences
        return text;
    }
}