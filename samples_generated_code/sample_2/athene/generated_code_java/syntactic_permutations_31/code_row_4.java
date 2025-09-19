import java.net.URL;

public class RedirectHandler {

    public static void main(String[] args) {
        String url = "https://example.com/path?query=value";
        System.out.println(redirect_url(url));
    }

    public static String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            return parsedUrl.toString();
        } catch (Exception e) {
            return "Invalid URL";
        }
    }
}