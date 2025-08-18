import java.net.MalformedURLException;
import java.net.URL;

public class UrlRedirector {

    public static void main(String[] args) {
        String testUrl = "https://www.example.com/path?query=1";
        try {
            System.out.println(redirectUrl(testUrl));
        } catch (MalformedURLException e) {
            System.err.println("Invalid URL: " + testUrl);
        }
    }

    public static String redirectUrl(String urlString) throws MalformedURLException {
        URL url = new URL(urlString);
        return url.getHost();
    }
}