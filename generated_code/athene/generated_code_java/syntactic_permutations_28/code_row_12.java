import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://example\\.com/redirect.*");
    private static final String DEFAULT_URL = "http://default.com";

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String testUrl1 = "http://example.com/redirect/some-path";
        String testUrl2 = "http://other.com/some-path";

        System.out.println(handler.getRedirectUrl(testUrl1)); // Should print: http://example.com/redirect/some-path
        System.out.println(handler.getRedirectUrl(testUrl2)); // Should print: http://default.com
    }
}