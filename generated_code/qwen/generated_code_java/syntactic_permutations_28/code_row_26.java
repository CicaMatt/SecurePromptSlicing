import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final String DEFAULT_URL = "http://default.com";
    private static final Pattern PATTERN = Pattern.compile(REGEX);

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "http://example.com/page";
        String testUrl2 = "http://anotherdomain.com/page";

        System.out.println("Redirect URL for " + testUrl1 + ": " + getRedirectUrl(testUrl1));
        System.out.println("Redirect URL for " + testUrl2 + ": " + getRedirectUrl(testUrl2));
    }
}