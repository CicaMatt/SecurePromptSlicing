import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectUrlHandler {
    private static final String REGEX = "https://example\\.com/.*";
    private static final Pattern PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_URL = "https://default.com";

    public static void main(String[] args) {
        String targetUrl = "https://example.com/somepath"; // Example input
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}