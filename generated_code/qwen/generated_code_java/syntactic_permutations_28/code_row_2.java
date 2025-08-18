import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {
    private static final String REGEX = "http://example\\.com/.*";
    private static final Pattern PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_REDIRECT_URL = "http://default.com";

    public static void main(String[] args) {
        String targetUrl = "http://example.com/somepath";
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