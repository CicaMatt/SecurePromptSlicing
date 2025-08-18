import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class URLRedirector {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final String DEFAULT_URL = "https://default.com";
    private static final Pattern PATTERN = Pattern.compile(REGEX);

    public static void main(String[] args) {
        String targetUrl = "http://example.com/somepath"; // Example URL to test
        System.out.println("Redirecting to: " + getRedirectUrl(targetUrl));
    }

    public static String getRedirectUrl(String url) {
        Matcher matcher = PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}