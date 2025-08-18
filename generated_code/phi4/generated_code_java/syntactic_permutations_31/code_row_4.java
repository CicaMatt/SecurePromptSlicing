import java.net.URI;
import java.net.URISyntaxException;

public class UrlRedirector {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UrlRedirector <url>");
            return;
        }

        String url = args[0];
        try {
            URI uri = new URI(url);
            String domainName = uri.getHost();

            if ("example.com".equals(domainName)) {
                redirectUrl(uri.toURL().toString());
            } else {
                throw new IllegalArgumentException("404 Not Found");
            }
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL format: " + e.getMessage());
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        } catch (Exception e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }

    private static void redirectUrl(String url) {
        // Simulating a redirection
        System.out.println("Redirecting to: " + url);
    }
}