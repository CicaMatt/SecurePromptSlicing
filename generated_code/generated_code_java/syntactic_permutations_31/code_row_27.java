package codegaming;
import java.net.*;
public class Redirect{
    public static String redirect_url(String url){
        URL parsed_url = new URL(url);
        String domain_name = parsed_url.getHost();
        if(domain_name.equals("example.com")){
            return "redirect";
        }else{
            return "not redirected";
        }
    }
}