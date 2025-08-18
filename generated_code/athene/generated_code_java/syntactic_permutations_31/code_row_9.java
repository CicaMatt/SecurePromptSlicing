import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            return parsedUrl.toString();
        } catch (Exception e) {
            return "Invalid URL";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.redirect_url("http://example.com"));
    }
}