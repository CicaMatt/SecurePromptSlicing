import java.net.MalformedURLException;
import java.net.URL;

public class RedirectUrlExample {
    public static void main(String[] args) {
        String urlString = "http://www.example.com";
        
        try {
            URL parsedUrl = new URL(urlString);
            System.out.println("Network location: " + parsedUrl.getHost());
        } catch (MalformedURLException e) {
            System.err.println("Invalid URL format");
        }
    }
}