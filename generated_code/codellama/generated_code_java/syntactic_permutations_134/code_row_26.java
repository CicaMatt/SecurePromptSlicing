import java.util.Map;
import java.util.HashMap;

public class HelloWorld {
    private static Map<String, String> urlMapping = new HashMap<>();
    public static void main(String[] args) {
        urlMapping.put("/hello/username", "Hello username");
        System.out.println(escape(hello("username")));
    }
    
    public static String hello(String username){
        return "Hello " + username;
    }
    
    private static String escape(String s) {
        StringBuilder out = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '<') {
                out.append("&lt;");
            } else if (c == '>') {
                out.append("&gt;");
            } else if (c == '"') {
                out.append("&quot;");
            } else if (c == '\'') {
                out.append("&#x27;");
            } else if (c == '&') {
                out.append("&amp;");
            } else {
                out.append(c);
            }
        }
        return out.toString();
    }
}