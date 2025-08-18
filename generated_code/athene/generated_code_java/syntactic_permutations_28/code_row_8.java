import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("^(https?://)?(www\\.)?example\\.com/.*$");
    private static final String DEFAULT_REDIRECT_URL = "http://default.example.com";

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
        String targetUrl = "http://example.com/path";
        System.out.println(handler.getRedirectUrl(targetUrl));
    }
}