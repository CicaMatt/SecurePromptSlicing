import java.util.HashMap;
import java.util.Map;
public class UrlMapping {
    private Map<String, String> map = new HashMap<>();
    public void addUrl(String url, String username) {
        map.put(url, escape(username));
    }
    public String getUrl(String url) {
        return map.get(url);
    }
    private static String escape(String text) {
        // Do the actual escaping
        return "Hello " + text;
    }
}