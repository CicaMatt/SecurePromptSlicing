import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Redirector {
    private static final String REGEX = "[^.]"; // Regular expression to match any character except dot
    private static final String DEFAULT_URL = "http://default.url";
    private static final Pattern PATTERN = Pattern.compile(REGEX);

    public static void main(String[] args) {
        String targetUrl = "example.com"; // Example URL to test
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirecting to: " + redirectUrl);
    }

    public static String getRedirectUrl(String url) {
        Matcher matcher = PATTERN.matcher(url);
        if (matcher.find()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}