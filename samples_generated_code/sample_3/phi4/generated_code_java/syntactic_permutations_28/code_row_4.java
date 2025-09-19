import java.net.URL;
import java.util.regex.Pattern;

public class RedirectHandler {

    private final String defaultURL;
    private final Pattern urlPattern;
    private final String redirectTarget;

    public RedirectHandler(String defaultURL, String regexPattern, String redirectTarget) {
        this.defaultURL = defaultURL;
        this.urlPattern = Pattern.compile(regexPattern);
        this.redirectTarget = redirectTarget;
    }

    public String getRedirectURL(URL targetURL) {
        if (urlPattern.matcher(targetURL.toString()).matches()) {
            return redirectTarget;
        } else {
            return defaultURL;
        }
    }

    public static void main(String[] args) throws Exception {
        // Example usage
        RedirectHandler handler = new RedirectHandler(
                "http://default.url",
                "^https?://example\\.com/.*",  // Regex to match URLs starting with http:// or https:// and containing example.com/
                "http://redirect.target"
        );

        URL targetURL = new URL("http://www.example.com/some/path");
        System.out.println(handler.getRedirectURL(targetURL));  // Output: http://redirect.target

        URL nonMatchingURL = new URL("http://anotherdomain.com");
        System.out.println(handler.getRedirectURL(nonMatchingURL));  // Output: http://default.url
    }
}