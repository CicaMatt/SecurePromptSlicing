import java.io.IOException;

public class Decorator {
    public static void bind(String url, String pong) {
        if (System.getenv("ping").equals("0")){
            System.out.println("URL is not alive");
            return;
        } 
        System.out.println("URL is alive");
        
    }
}