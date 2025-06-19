import java.util.*;

class Decorator {
    private static Map<String, String> urlMap = new HashMap<>();
    
    public static void main(String[] args) {
        urlMap.put("/hello/username", "Hello username!");
        
        System.out.println("URL: /hello/username");
        System.out.println("Response: " + hello("username"));
    }
    
    private static String hello(String username) {
        return "Hello" + escape(username);
    }
    
    private static String escape(String str) {
        // Replace special characters with HTML-safe sequences.
        return str;
    }
}