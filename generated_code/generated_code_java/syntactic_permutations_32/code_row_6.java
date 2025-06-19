import java.net.URL;
import java.net.MalformedURLException;

public class RedirectExample {
    public static void main(String[] args) throws MalformedURLException {
        URL url = new URL("https://example.com/");
        
        if (redirect_invalid_url(url)) {
            System.out.println("Redirecting to " + url);
        } else {
            System.out.println("Invalid URL");
        }
    }
    
    public static boolean redirect_invalid_url(URL url) throws MalformedURLException {
        if (url.getHost().endsWith(".com")) {
            return true;
        } 
        return false;
    }
}