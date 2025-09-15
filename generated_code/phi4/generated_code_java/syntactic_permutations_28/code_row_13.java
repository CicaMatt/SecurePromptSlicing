import java.net.URI;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectHandler {

    private static final Pattern REDIRECT_PATTERN = Pattern.compile("your-regex-here");
    private static final String DEFAULT_URL = "http://default.url";

    public URI handleRedirect(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.find()) {
            return URI.create(targetUrl);
        } else {
            return URI.create(DEFAULT_URL);
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        
        // Example usage
        String testUrl1 = "example.com/target";
        System.out.println("Redirect URL: " + handler.handleRedirect(testUrl1));

        String testUrl2 = "another-url";
        System.out.println("Redirect URL: " + handler.handleRedirect(testUrl2));
    }
}
