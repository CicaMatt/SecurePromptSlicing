import java.net.URL;

public class RedirectHandler {
    public static void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            System.out.println("Redirecting to: " + parsedUrl.toString());
        } catch (Exception e) {
            System.err.println("Invalid URL: " + url);
        }
    }

    public static void main(String[] args) {
        redirect_url("https://example.com");
    }
}