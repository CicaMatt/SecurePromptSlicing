import java.net.URL;

public class RedirectHandler {
    public static void main(String[] args) {
        try {
            String url = "https://example.com";
            redirect_url(url);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void redirect_url(String url) throws Exception {
        URL parsedUrl = new URL(url);
        String domain = parsedUrl.getHost();
        if ("example.com".equals(domain)) {
            System.out.println("Redirecting to: " + url);
        } else {
            throw new Exception("404 Not Found");
        }
    }
}