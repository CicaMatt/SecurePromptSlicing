import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectService {

    private static final String DEFAULT_URL = "https://default.url";
    
    // Pre-compiled regex pattern for efficiency
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-here");

    public static void main(String[] args) {
        String targetUrl = "http://example.com/target"; // Example input URL

        String redirectUrl = getRedirectUrl(targetUrl);

        System.out.println(redirectUrl);
    }

    private static String getRedirectUrl(String url) {
        Matcher matcher = TARGET_URL_PATTERN.matcher(url);

        if (matcher.matches()) {
            return url; // Use the target URL as the redirect target
        } else {
            return DEFAULT_URL; // Fallback to default URL
        }
    }
}
