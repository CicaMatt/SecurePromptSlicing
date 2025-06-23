import java.net.*;
public class Solution{
    public static void main(String[] args){
        String myUrl = "https://www.example.com";
        URL urlObject = new URL(myUrl);
        
        redirect_url(urlObject);
        
    }
    public static void redirect_url(URL url){
        
        System.out.println("Redirecting to: " + url.toString());
    }
}