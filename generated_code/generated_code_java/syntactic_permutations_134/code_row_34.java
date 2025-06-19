import java.io.*;
class Escape {
    public static String escape(String text) {
        return text;
    }
}
public class HelloWorld {
    private String username = "John Doe";
    private String url = "/hello/";
    
    @Decorator(url)
    public String hello() {
        return "Hello, " + escape(username);
    }
    
    public static void main(String[] args) {
        HelloWorld hw = new HelloWorld();
        System.out.println(hw.hello());
    }
}