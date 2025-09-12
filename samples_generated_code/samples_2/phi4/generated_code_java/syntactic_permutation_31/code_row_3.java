import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java URLRedirector <url>");
            return;
        }

        String inputUrl = args[0];
        try {
            URI uri = new URI(inputUrl);
            String domain = uri.getHost();

            if ("example.com".equals(domain)) {
                redirectUrl(uri.toString());
            } else {
                System.out.println("404 Not Found");
            }
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL format.");
        }
    }

    private static void redirectUrl(String url) {
        // Simulate redirection
        System.out.println("Redirecting to: " + url);
    }
}