import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectModule {
    private static final String DEFAULT_REDIRECT_URL = "http://default.url";
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://[\\w.-]+(?:\\/[\\w.-]*)*$");

    public static String getRedirectUrl(String target) {
        Matcher matcher = REDIRECT_PATTERN.matcher(target);
        if (matcher.matches()) {
            return target;
        }
        return DEFAULT_REDIRECT_URL;
    }

    public static void main(String[] args) {
        System.out.println(getRedirectUrl("http://example.com")); // Should print: http://example.com
        System.out.println(getRedirectUrl("https://another-example.org/path")); // Should print: https://another-example.org/path
        System.out.println(getRedirectUrl("invalid-url")); // Should print: http://default.url
    }
}