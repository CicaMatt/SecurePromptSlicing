import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                return "https://new.example.com";
            } else {
                throw new RuntimeException("404 Error");
            }
        } catch (Exception e) {
            throw new RuntimeException("404 Error", e);
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        try {
            System.out.println(handler.redirect_url("http://example.com"));
        } catch (RuntimeException e) {
            System.err.println(e.getMessage());
        }
    }
}