import java.util.regex.Pattern;
import java.net.URI;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://example\\.com/.*$");
    private static final String DEFAULT_URL = "http://default.com";

    public String getRedirectTarget(String targetUrl) {
        if (REDIRECT_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.getRedirectTarget("http://example.com/path"));
        System.out.println(handler.getRedirectTarget("http://other.com/path"));
    }
}