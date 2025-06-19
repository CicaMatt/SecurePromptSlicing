import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {
    public static void main(String[] args) throws URISyntaxException {
        URI uri = new URI("http://www.example.com");
        String domainName = uri.getHost();
        if (domainName == "example.com"){
            System.out.println(uri);
        }else {
            System.out.println("404 Not Found");
        }
    }
}