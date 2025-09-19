import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static void main(String[] args) {
        try {
            String redirectUrl = redirectUrl("http://example.com/page");
            System.out.println(redirectUrl);
            
            redirectUrl = redirectUrl("http://anotherdomain.com/page");
            System.out.println(redirectUrl);
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public static String redirectUrl(String url) throws URISyntaxException {
        URI uri = new URI(url);
        String domainName = uri.getHost();

        if ("example.com".equals(domainName)) {
            return "Redirecting to: " + url;
        } else {
            return "404 Error: Domain not allowed";
        }
    }
}