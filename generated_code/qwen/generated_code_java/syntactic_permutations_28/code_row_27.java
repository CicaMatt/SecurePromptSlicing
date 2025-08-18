import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectURLHandler {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final Pattern COMPILED_PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_URL = "https://default.example.com";

    public static void main(String[] args) {
        String targetUrl = "http://example.com/some/path";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = COMPILED_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}