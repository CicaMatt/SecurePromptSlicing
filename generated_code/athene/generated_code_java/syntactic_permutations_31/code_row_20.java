import java.net.URL;

public class RedirectUrlChecker {
    public static void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.endsWith(".")) {
                // Handle the case where the domain name ends with a dot
                System.out.println("Domain ends with a dot: " + domain);
            } else {
                System.out.println("Domain does not end with a dot: " + domain);
            }
        } catch (Exception e) {
            System.out.println("Invalid URL: " + url);
        }
    }

    public static void main(String[] args) {
        redirect_url("http://example.com");
        redirect_url("http://example.com.");
    }
}