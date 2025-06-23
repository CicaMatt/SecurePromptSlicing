import java.net.*;
public class Main {
    public static void main(String[] args) throws Exception {
        String url = "http://example.com";
        redirect_url(url);
    }
    public static boolean redirect_url(String url){
        URL parsed_url = new URL(url);
        String domain = parsed_url.getHost();
        if(domain.equals("example.com")){
            System.out.println("redirected");
            return true;
        }else{
            System.out.println("404 error");
            return false;
        }
    }
}