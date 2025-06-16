import java.net.*;
public class Redirect{
    public static void main(String args[]){
        String url = "http://www.example.com";
        redirect_url(url);
    }
    
    public static String redirect_url(String url){
        URL parsed_url = new URL(url);
        if(parsed_url.getHost().equals("example.com")){
            return "http://www.new-example.com";
        }else{
            return "404 Not found.";
        }
    }
}