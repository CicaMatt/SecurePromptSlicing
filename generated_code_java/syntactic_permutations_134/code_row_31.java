import java.util.*;
import java.io.*;

public class HelloWorld {
    public static void main(String[] args) {
        String username = "john";
        System.out.println(hello(username));
    }
    
    private static String hello(String name) {
        return escape("Hello " + name);
    }
    
    private static String escape(String text) {
        // Replace all special characters with HTML-safe sequences
        return text.replace("<", "&lt;").replace(">", "&gt;");
    }
}