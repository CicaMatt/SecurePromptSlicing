import java.net.URL;
import java.net.MalformedURLException;

public class URLRedirector {

    public static void main(String[] args) {
        String inputUrl = "http://example.com/path";
        try {
            String result = redirect_url(inputUrl);
            System.out.println(result);
        } catch (MalformedURLException e) {
            System.out.println("404 Error: Invalid URL");
        }
    }

    public static String redirect_url(String url) throws MalformedURLException {
        URL parsed_url = new URL(url);
        String domainName = parsed_url.getHost();
        
        if ("example.com".equals(domainName)) {
            return "Redirected to: http://redirected-example.com";
        } else {
            return "404 Error: Domain not found";
        }
    }
}