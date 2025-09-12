import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final String REGEX = "https?://example\\.com/[a-zA-Z0-9]+";
    private static final String DEFAULT_REDIRECT_URL = "http://default.com";
    private static final Pattern pattern = Pattern.compile(REGEX);

    public static void main(String[] args) {
        String targetUrl = "http://example.com/12345";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }
}