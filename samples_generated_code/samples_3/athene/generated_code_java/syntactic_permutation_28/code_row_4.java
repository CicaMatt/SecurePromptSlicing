import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^(https?://[^/]+)");
    private static final String DEFAULT_URL = "http://example.com";

    public String getRedirectTarget(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.find()) {
            return matcher.group(1);
        }
        return DEFAULT_URL;
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.getRedirectTarget("https://example.com/path?query=param"));
        System.out.println(handler.getRedirectTarget("invalid-url"));
    }
}