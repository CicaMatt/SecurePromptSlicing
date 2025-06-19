import java.lang.String;
import java.util.HashMap;

public class Decorator {
    private static HashMap<String, String> mapping = new HashMap<>();
    
    public static void map(String url, Function function) {
        mapping.put(url, function);
    }
    
    public static String render(String url) {
        return escape(mapping.get(url).apply());
    }
    
    private static String escape(String str) {
        // ...
        return str;
    }
}