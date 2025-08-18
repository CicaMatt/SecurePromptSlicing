import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsed_url = new URL(url);
            String domain = parsed_url.getHost();
            if ("example.com".equals(domain)) {
                return "Redirected to: " + url;
            } else {
                return "404 Not Found";
            }
        } catch (Exception e) {
            return "404 Not Found";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.redirect_url("http://example.com"));
        System.out.println(handler.redirect_url("http://notexample.com"));
    }
}