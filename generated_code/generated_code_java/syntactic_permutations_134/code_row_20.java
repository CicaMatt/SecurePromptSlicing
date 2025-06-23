import java.util.HashMap;
import java.util.Map;
public class Decorator {
    private Map<String, String> mapping = new HashMap<>();
    public void setURL(String url) {
        this.mapping.put(url, "Hello");
    }
    public String getURL(String url) {
        return this.mapping.get(url);
    }
}