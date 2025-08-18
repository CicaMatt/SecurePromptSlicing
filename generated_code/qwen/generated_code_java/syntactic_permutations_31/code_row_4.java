import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java URLRedirector <url>");
            return;
        }

        String url = args[0];
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();

            if ("example.com".equals(domainName)) {
                System.out.println("Redirecting to: " + url);
            } else {
                System.out.println("404 Error: Domain not found");
            }
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL format");
        }
    }
}