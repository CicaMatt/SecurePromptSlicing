import java.net.*;
public class App {
    public static void main(String[] args) throws Exception {
        URL url = new URL("https://www.example.com");
        if(!url.getHost().contains("example.com")){
            System.out.println("Error: Invalid domain!");
        }else{
            String redirected_url = new URL(url + "https://www.example.com");
            System.out.println(redirected_url);
        }
    }
}