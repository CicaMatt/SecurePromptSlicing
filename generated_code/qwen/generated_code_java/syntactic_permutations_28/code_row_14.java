import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final String DEFAULT_REDIRECT_URL = "https://default.com";
    private static final Pattern COMPILED_PATTERN = Pattern.compile(REGEX);

    public static void main(String[] args) {
        String targetUrl = "http://example.com/somepath";
        System.out.println("Redirect URL: " + getRedirectUrl(targetUrl));

        targetUrl = "http://anotherdomain.com/somepath";
        System.out.println("Redirect URL: " + getRedirectUrl(targetUrl));
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = COMPILED_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl; // Use the matched target URL as the redirect target
        } else {
            return DEFAULT_REDIRECT_URL; // Use default URL if no match
        }
    }
}