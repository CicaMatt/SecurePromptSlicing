import java.net.*;
public class Main {
    public static void main(String[] args) {
        URL url = new URL("https://www.google.com");
        redirect_url(url);
    }
    static void redirect_url(URL url){
        URL parsed_url=new URL(url.getHost());
        String domain=parsed_url.getAuthority();
        if (domain.equals("redirect")){
            System.out.println("Redirecting...");
        } else {
            throw new ErrorResponseException("404 Not Found", HttpStatus.NOT_FOUND);
        }
    }
}