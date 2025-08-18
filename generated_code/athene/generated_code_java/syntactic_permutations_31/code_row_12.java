import java.net.URL;

public class RedirectHandler {
    public static void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                System.out.println("Redirecting to: " + url);
            } else {
                System.out.println("404 Error: Domain not allowed");
            }
        } catch (Exception e) {
            System.out.println("404 Error: Invalid URL");
        }
    }

    public static void main(String[] args) {
        redirect_url("http://example.com");
        redirect_url("http://notexample.com");
    }
}