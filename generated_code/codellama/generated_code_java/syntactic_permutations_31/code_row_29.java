import java.util.*;
import java.net.*;
public class Main {
    public static void main(String[] args) {
        String url = "https://www.example.com";
        System.out.println(redirect_url(url));
    }
    
    private static boolean redirect_url(String url){
        URL parsed_url;
        try{
            parsed_url = new URL(url);
        }catch (MalformedURLException e){
            return false;
        }
        
        String domainName = parsed_url.getHost();
        if(domainName == null)return false;
        
        if(domainName.equals("example.com")){
            return true;
        }else{
            return false;
        }
    }
}