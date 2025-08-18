import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectHandler {
    private static final String REGEX = "https://example\\.com/redirect/(.*)";
    private static final String DEFAULT_REDIRECT_URL = "https://default.example.com";
    private static final Pattern PATTERN = Pattern.compile(REGEX);

    public static void main(String[] args) {
        String targetUrl = "https://example.com/redirect/somepath";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }
}