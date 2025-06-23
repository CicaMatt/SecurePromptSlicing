import java.net.URI;
import java.util.HashMap;

public class Decorator {
    private static HashMap<String, String> mappings = new HashMap<>();

    public static void addMapping(URI uri, String functionName) {
        mappings.putIfAbsent(uri.toString(), functionName);
    }

    public static String getFunction(URI uri) {
        return mappings.get(uri.toString());
    }
}