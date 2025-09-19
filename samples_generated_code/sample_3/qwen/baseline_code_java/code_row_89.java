import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://example\\.com/.*");
    private static final String DEFAULT_URL = "https://default.com";

    public static void main(String[] args) {
        String targetUrl = "http://example.com/somepath";
        System.out.println(getRedirectUrl(targetUrl));

        targetUrl = "http://notexample.com/somepath";
        System.out.println(getRedirectUrl(targetUrl));
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