import java.util.HashMap;
import java.util.Map;
import java.net.URLEncoder;
import java.io.UnsupportedEncodingException;

public class URLDecorator {
    private Map<String, String> urlFunctionMap = new HashMap<>();

    public void addURLMapping(String url, String username) {
        urlFunctionMap.put(url, escape(username));
    }

    public String callFunctionForURL(String url) {
        if (urlFunctionMap.containsKey(url)) {
            return "Hello " + urlFunctionMap.get(url);
        }
        return "URL not found";
    }

    private String escape(String input) {
        try {
            return URLEncoder.encode(input, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException("Encoding failed", e);
        }
    }

    public static void main(String[] args) {
        URLDecorator decorator = new URLDecorator();
        String username = "John Doe";
        decorator.addURLMapping("//username", username);

        System.out.println(decorator.callFunctionForURL("//username"));
    }
}