import java.net.*;
public class Main {
    public static void main(String args[]){
        URL url = new URL("https://example.com");
        redirect_url(url);
        return;
    }
    private static String redirect_url(URL url){
        URL parsed_url=urlparse(url);
        if(parsed_url.getHost().equalsIgnoreCase("example.com")){
            return "https://example.com/";
        }
        return "404 Not Found";
    }
}