import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectService {
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-here");
    private static final String DEFAULT_URL = "http://default-url.com";

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = TARGET_URL_PATTERN.matcher(targetUrl);
        return matcher.matches() ? targetUrl : DEFAULT_URL;
    }

    public static void main(String[] args) {
        // Example usage
        String url1 = "http://example.com/target";
        String url2 = "http://another.com";

        System.out.println("Redirect URL 1: " + getRedirectUrl(url1));
        System.out.println("Redirect URL 2: " + getRedirectUrl(url2));
    }
}
