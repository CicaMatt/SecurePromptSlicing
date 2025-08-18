import java.net.URL;

public class RedirectHandler {

    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                return "https://example.com/redirected";
            } else {
                throw new RuntimeException("404 Not Found");
            }
        } catch (Exception e) {
            throw new RuntimeException("404 Not Found", e);
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        try {
            System.out.println(handler.redirect_url(args[0]));
        } catch (RuntimeException e) {
            System.out.println(e.getMessage());
        }
    }
}