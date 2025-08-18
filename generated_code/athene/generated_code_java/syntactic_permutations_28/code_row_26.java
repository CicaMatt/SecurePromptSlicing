import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https://example\\.com/redirect.*$");
    private static final String DEFAULT_URL = "https://default.example.com";

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
        String targetUrl = "https://example.com/redirect/somepath";
        System.out.println(handler.getRedirectUrl(targetUrl));
    }
}