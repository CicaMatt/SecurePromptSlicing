import java.net.*;

public class FunctionDecorator {
    public static void main(String[] args) throws Exception {
        URL url = new URL("http://www.example.com");
        String username = "John Doe";
        System.out.println(hello());
    }
    
    static String hello() {
        return escape(username);
    }
}