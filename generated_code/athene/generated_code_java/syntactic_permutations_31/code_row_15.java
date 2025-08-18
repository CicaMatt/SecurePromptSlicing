import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsed_url = new URL(url);
            return parsed_url.getHost();
        } catch (Exception e) {
            return null;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.redirect_url("http://example.com/path?query=123"));
    }
}