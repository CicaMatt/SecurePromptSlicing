import java.net.*;

public class RedirectUrl{
   public static void main(String[] args){
      String url = "https://www.example.com";
      try {
         URL redirect_url = new URL(url);
         
         URI uri = new URI(redirect_url.getProtocol(), null, 
            redirect_url.getHost(), redirect_url.getPort(), 
            redirect_url.getPath(), redirect_url.getQuery(), 
            redirect_url.getRef());
            
         String domainName=uri.getHost();
         if(domainName.equals("example.com")){
            System.out.println("URL is redirected");
         }else {
            System.out.println("404 error");
         }
      }catch (Exception e) {
         e.printStackTrace();
      }
   }
}