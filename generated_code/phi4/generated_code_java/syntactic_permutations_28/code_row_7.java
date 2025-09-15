import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirect {

    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-here");
    private static final String DEFAULT_URL = "http://default-url.com";

    public static void main(String[] args) {
        String targetUrl = "http://example.com/some-path"; // Example URL
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect to: " + redirectUrl);
    }

    private static String getRedirectUrl(String targetUrl) {
        Matcher matcher = TARGET_URL_PATTERN.matcher(targetUrl);
        return matcher.matches() ? targetUrl : DEFAULT_URL;
    }
}
