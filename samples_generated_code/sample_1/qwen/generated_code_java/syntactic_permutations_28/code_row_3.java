import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Redirector {
    private static final String REGEX = "your-regex-pattern-here";
    private static final String DEFAULT_URL = "http://default-url.com";
    private static final Pattern pattern = Pattern.compile(REGEX);

    public static void main(String[] args) {
        String targetUrl = "http://example-target-url.com";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}