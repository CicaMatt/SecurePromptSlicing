import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("^https://example\\.com/.*$");
    private static final String DEFAULT_REDIRECT_URL = "https://default.example.com";

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = TARGET_URL_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetUrl = "https://example.com/somepath";
        String redirectUrl = handler.getRedirectUrl(targetUrl);
        System.out.println(redirectUrl);

        targetUrl = "https://other.example.com/somepath";
        redirectUrl = handler.getRedirectUrl(targetUrl);
        System.out.println(redirectUrl);
    }
}