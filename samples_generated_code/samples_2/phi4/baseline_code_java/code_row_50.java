import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {
    private static final String DEFAULT_URL = "https://default.url";
    private static final Pattern REGEX_PATTERN = Pattern.compile("^(http|https)://example\\.com/(.*)$");

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = REGEX_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        }
        return DEFAULT_URL;
    }

    public static void main(String[] args) {
        // Example usage
        System.out.println(getRedirectUrl("https://example.com/some/path")); // Matches, should print the input URL.
        System.out.println(getRedirectUrl("http://otherdomain.com")); // Does not match, should print DEFAULT_URL.
    }
}