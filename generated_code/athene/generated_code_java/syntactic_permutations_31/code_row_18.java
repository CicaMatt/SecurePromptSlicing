import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.endsWith(".")) {
                domain = domain.substring(0, domain.length() - 1);
            }
            return domain;
        } catch (Exception e) {
            return null;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String url = "http://example.com/path?query=param";
        System.out.println(handler.redirect_url(url));
    }
}