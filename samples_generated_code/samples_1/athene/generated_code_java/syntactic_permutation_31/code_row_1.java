import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
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