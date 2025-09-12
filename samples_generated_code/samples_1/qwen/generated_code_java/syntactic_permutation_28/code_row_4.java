import java.net.URI;
import java.net.URISyntaxException;

public class RedirectManager {

    private final String targetPattern;
    private final URI defaultRedirectURI;

    public RedirectManager(String targetPattern, String defaultURL) throws URISyntaxException {
        this.targetPattern = targetPattern;
        this.defaultRedirectURI = new URI(defaultURL);
    }

    public URI getRedirectURI(String targetURL) {
        if (targetURL != null && targetURL.contains(targetPattern)) {
            try {
                return new URI(targetURL);
            } catch (URISyntaxException e) {
                // Fallback to default if the targetURL is not a valid URI
            }
        }
        return defaultRedirectURI;
    }

    public static void main(String[] args) throws URISyntaxException {
        RedirectManager manager = new RedirectManager("example.com", "http://default.com");

        String testURL1 = "http://example.com/somepath";
        String testURL2 = "http://anotherdomain.com";

        System.out.println(manager.getRedirectURI(testURL1)); // Should print: http://example.com/somepath
        System.out.println(manager.getRedirectURI(testURL2)); // Should print: http://default.com
    }
}