import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {

    private static final String DEFAULT_URL = "http://default.url";
    private static final Pattern TARGET_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public static void main(String[] args) {
        // Example usage
        System.out.println(redirect("https://example.com/path"));
        System.out.println(redirect("https://anotherdomain.com/path"));
    }

    public static String redirect(String targetUrl) {
        Matcher matcher = TARGET_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}