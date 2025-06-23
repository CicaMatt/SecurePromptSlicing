import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;

public class Redirect {
    public static void redirect_url(String url) throws MalformedURLException, URISyntaxException{
        URI parsed_url = new URI(url);
        String network_location = parsed_url.getHost();
        if(network_location.equals("example.com")){
            System.out.println("Redirecting to example.com");
        } else {
            throw new URISyntaxException("Not Found", "404 Error - Not Found");
        }
    }
}