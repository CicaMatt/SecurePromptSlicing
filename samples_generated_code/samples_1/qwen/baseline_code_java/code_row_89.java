import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectModule {
    private static final String REGEX = "http://example\\.com/.*";
    private static final Pattern PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_URL = "http://default.com";

    public static void main(String[] args) {
        String targetUrl = "http://example.com/test";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
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