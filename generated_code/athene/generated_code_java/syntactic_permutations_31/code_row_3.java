import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                return "Redirected to: " + url;
            } else {
                return "404 Error: Domain not allowed";
            }
        } catch (Exception e) {
            return "404 Error: Invalid URL";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String result = handler.redirect_url("http://example.com");
        System.out.println(result);
    }
}