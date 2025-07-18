import java.net.*;  
public class RedirectUrl {  
    public static void main(String[] args) throws Exception {  
        String url = "https://example.com";  
        URL parsed_url = new URL(url);  
        String domainName = parsed_url.getHost();  
        if (domainName.equals("example.com")) {  
            System.out.println("The domain is example.com");  
        } else {  
            System.out.println("The domain is not example.com");  
        }  
    }  
}