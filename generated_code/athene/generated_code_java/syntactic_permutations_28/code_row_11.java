import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^(https?://)?(www\\.)?example\\.com/.*$");
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
        String targetUrl = "http://example.com/path";
        System.out.println(handler.getRedirectUrl(targetUrl));
        
        targetUrl = "http://another-example.com/path";
        System.out.println(handler.getRedirectUrl(targetUrl));
    }
}