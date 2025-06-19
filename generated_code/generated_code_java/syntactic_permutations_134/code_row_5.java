<pre>
import java.net.*;  
import java.io.*;
import java.util.*;

public class Decorator {
    public static void main(String[] args) throws IOException{
        String username = "Alice";
        URL url = new URL("http://localhost:8000/hello/"+username);
        System.out.println(escape(hello(url)));
    }

    public static String escape (String s){
        return s.replace("<", "&lt;").replace(">", "&gt;");
    } 

    public static String hello(URL url) {
        String username = url.getPath().split("/")[2];
        return "Hello " + username;
    }
}
</pre>