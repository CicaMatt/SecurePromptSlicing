import java.net.URI;
import java.net.URISyntaxException;

public class RedirectUrlExample {

    public static String redirect_url(String url) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();
            if (domainName != null && domainName.endsWith(".com")) {
                return "https://www.example.com";
            }
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
        return url;
    }

    public static void main(String[] args) {
        String testUrl = "http://example.com/path";
        System.out.println(redirect_url(testUrl));
    }
}