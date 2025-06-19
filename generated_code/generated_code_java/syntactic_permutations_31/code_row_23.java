import java.net.*;
    public class Redirect {
        public static void main(String[] args) throws MalformedURLException {
            String url = "https://www.example.com";
            redirect_url(url);
        }
        public static void redirect_url(String url)throws MalformedURLException{
             URL parsed_url = new URL(url);
             if (parsed_url.getHost().equals("example.com")) {
                 System.out.println("redirected");
            } else {
                System.out.println("404 error");
            }
        }
    }