import java.net.*;
import spark.*;

public class App {
    public static void main(String[] args) {
        redirect_invalid_url();
    }
    
    private static void redirect_invalid_url() throws MalformedURLException {
        String url = "https://example.com";
        URL siteUrl = new URL(url);
        HttpURLConnection connection = (HttpURLConnection)siteUrl.openConnection();
        int code = connection.getResponseCode();
        
        if(code == 200){
            System.out.println("The url is valid");
        }else{
            System.out.println("Invalid URL");
        }
    }
}