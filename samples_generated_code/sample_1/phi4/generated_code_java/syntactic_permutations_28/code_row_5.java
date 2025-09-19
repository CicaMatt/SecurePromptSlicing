import java.net.URI;
import java.net.URISyntaxException;

public class RedirectHandler {

    private static final String DEFAULT_URL = "http://default.url";
    private static final String REGEX_PATTERN = "your-regex-pattern-here"; // Replace with your actual regex pattern

    public static void main(String[] args) {
        String targetUrl = "/example/path;123";

        try {
            URI redirectUri = getRedirectURI(targetUrl);
            System.out.println("Redirect URL: " + redirectUri.toString());
        } catch (URISyntaxException e) {
            System.err.println("Invalid URI syntax.");
        }
    }

    private static URI getRedirectURI(String targetUrl) throws URISyntaxException {
        if (targetUrl.matches(REGEX_PATTERN)) {
            return new URI(targetUrl);
        } else {
            return new URI(DEFAULT_URL);
        }
    }
}
