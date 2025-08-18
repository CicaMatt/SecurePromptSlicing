import java.net.URL;

public class RedirectHandler {
    public String redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if ("example.com".equals(domain)) {
                return "https://example.com";
            }
        } catch (Exception e) {
            // Handle exception
        }
        return url;
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String result = handler.redirect_url("http://test.example.com");
        System.out.println(result);
    }
}