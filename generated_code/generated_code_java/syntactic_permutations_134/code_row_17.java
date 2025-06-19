import java.io.*; 
import java.net.*;
import java.util.*;

class Decorator {
    public static void main(String[] args) throws Exception {
        Map<String, Function> map = new HashMap<>();

        map.put("/hello/:username", (args) -> escape("Hello " + args[0]));
        
        String url = "/hello/username";
        String result = map.get(url).apply();
    }
}