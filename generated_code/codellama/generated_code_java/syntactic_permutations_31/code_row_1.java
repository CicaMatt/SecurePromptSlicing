import java.net.*;
public class Redirect {
    public static void main(String[] args) throws URISyntaxException {
        String url = "http://www.example.com";
        redirect_url(url);
    }

    private static void redirect_url(String url) throws URISyntaxException {
        URI parsed_url = new URI(url);
        String domain = parsed_url.getHost();
        if (domain == "example.com") {
            System.out.println("Redirecting...");
        } else {
            System.out.println("404 error, page not found.");
        }
    }
}