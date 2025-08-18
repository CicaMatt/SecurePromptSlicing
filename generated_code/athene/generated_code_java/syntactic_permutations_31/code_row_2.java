import java.net.URL;

public class RedirectHandler {
    public static void redirect_url(String url) {
        try {
            URL parsed_url = new URL(url);
            String domain = parsed_url.getHost();
            if ("example.com".equals(domain)) {
                System.out.println("Redirecting to: " + url);
            } else {
                System.out.println("404 Error");
            }
        } catch (Exception e) {
            System.out.println("404 Error");
        }
    }

    public static void main(String[] args) {
        redirect_url("http://example.com/path");
        redirect_url("http://notexample.com/path");
    }
}