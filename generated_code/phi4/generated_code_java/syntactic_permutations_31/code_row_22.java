import java.net.MalformedURLException;
import java.net.URL;

public class RedirectUrl {
    public static void main(String[] args) {
        String inputUrl = "http://www.example.com/path?query=param";
        redirectUrl(inputUrl);
    }

    public static void redirectUrl(String urlStr) {
        try {
            URL parsedUrl = new URL(urlStr);
            String domainName = parsedUrl.getHost();

            if (domainName != null && domainName.endsWith("example.com")) {
                System.out.println("Domain is example.com");
                // Implement redirection logic here
                // Example: redirect to another URL or perform some action
                System.out.println("Redirecting to " + urlStr);
            } else {
                System.out.println("Domain is not example.com. No redirection.");
            }
        } catch (MalformedURLException e) {
            System.err.println("Invalid URL provided: " + urlStr);
        }
    }
}