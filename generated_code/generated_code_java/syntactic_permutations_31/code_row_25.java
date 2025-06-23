import java.net.*;
public class RedirectUrl{
    public static void main(String[] args){
        String url = "http://www.example.com";
        URL parsed_url = new URL(url);
        String domainName = parsed_url.getHost();
        if(domainName == "example.com"){
            System.out.print("Redirected");
        }else{
            System.out.print("Not Redirected");
        }
    }
}