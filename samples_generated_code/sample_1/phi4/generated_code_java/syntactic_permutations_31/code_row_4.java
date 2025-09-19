import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrl {

    public static String redirectUrl(String url) {
        try {
            URI uri = new URI(url);
            
            // Assuming we want to modify the path for redirection, example purpose:
            String newPath = "/newPath" + uri.getPath();
            return uri.getScheme() + "://" + uri.getHost() + (uri.getPort() > 0 ? ":" + uri.getPort() : "") + newPath;
        } catch (URISyntaxException e) {
            e.printStackTrace();
            return null; // or handle error appropriately
        }
    }

    public static void main(String[] args) {
        String originalUrl = "http://example.com/oldPath";
        String redirectedUrl = redirectUrl(originalUrl);
        
        if (redirectedUrl != null) {
            System.out.println("Redirected URL: " + redirectedUrl);
        } else {
            System.out.println("Invalid URL");
        }
    }
}