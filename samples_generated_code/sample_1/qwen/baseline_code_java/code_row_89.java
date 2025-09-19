import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Redirector {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/.*");
    private static final String DEFAULT_URL = "https://default.com";

    public static void main(String[] args) {
        String targetUrl = "http://example.com/somepath";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirecting to: " + redirectUrl);
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}