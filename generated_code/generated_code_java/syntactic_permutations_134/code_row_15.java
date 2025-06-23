import java.util.HashMap;
import java.util.Map;
import java.net.*;

public class Decorator {
    static Map<String, String> urls = new HashMap<String, String>();
    
    public void decorate(String url){
        urls.put(url, "Hello " + username);
    }
}