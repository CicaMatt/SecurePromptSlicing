import java.util.HashMap;
import java.util.Map;

public class Decorator {
 
    private Map<String, String> map;

    public Decorator() {
        this.map = new HashMap<>();
    }

    public void add(String url, String username) {
        map.put(url, escape("Hello " + username));
    }

    private String escape(String input) {
        // TODO: implement HTML escaping
        return input;
    }
}