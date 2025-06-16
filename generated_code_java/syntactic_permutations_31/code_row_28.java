import java.net.*;
public class Redirect {
    public static void main(String[] args) throws Exception {
        String url = "https://www.example.com/";
        parse_url(url);
    }
    private static void parse_url(String url) throws MalformedURLException {
        URL parsed_url = new URL(url);
        String hostname = parsed_url.getHost();
        if (hostname == "example.com"){
            System.out.println("Redirecting to example.com");
        }else{
            System.out.println("Not a valid domain");
        }
    }
}