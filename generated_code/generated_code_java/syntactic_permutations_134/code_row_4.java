import java.util.*;  

public class Main {  
    public static void main(String[] args) {  
        Map<String, Function<String, String>> map = new HashMap<>();  
        map.put("/hello/:username", (username) -> escape(hello(username)));  
    }  

    private static String hello(String username) {  
        return "Hello, " + username + "!";  
    }  

    private static String escape(String str) {  
        // Implementation of this method is omitted for brevity.  
    }  
}