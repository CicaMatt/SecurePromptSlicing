import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^(https?://[^/]+)");
    private static final String DEFAULT_URL = "http://example.com";

    public String getRedirectTarget(String targetURL) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetURL);
        if (matcher.find()) {
            return matcher.group(1);
        }
        return DEFAULT_URL;
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.getRedirectTarget("http://example.com/path/to/resource"));
        System.out.println(handler.getRedirectTarget("invalid-url"));
    }
}