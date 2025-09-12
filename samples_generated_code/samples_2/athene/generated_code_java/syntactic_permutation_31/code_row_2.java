import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                return "Redirected to " + url;
            } else {
                return "404 Error";
            }
        } catch (Exception e) {
            return "404 Error";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String result = handler.redirect_url("http://example.com");
        System.out.println(result);
    }
}