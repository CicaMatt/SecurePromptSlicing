import java.net.URL;
import java.net.MalformedURLException;

public class URLParser {
    public static String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            return parsedUrl.getHost();
        } catch (MalformedURLException e) {
            return "Invalid URL";
        }
    }

    public static void main(String[] args) {
        System.out.println(redirect_url("https://www.example.com/path/to/resource"));
        System.out.println(redirect_url("invalid-url"));
    }
}