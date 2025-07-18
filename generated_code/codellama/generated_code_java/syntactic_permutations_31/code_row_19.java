import java.net.URL;
import java.util.regex.Pattern;

public class Redirect {
    public static String redirect_url(String url) {
        URL parsed_url = new URL(url);
        if (parsed_url.getHost().equals("example.com")) {
            return "https://www.example.com";
        } else {
            return "HTTP/1.1 404 Not Found";
        }
    }
}