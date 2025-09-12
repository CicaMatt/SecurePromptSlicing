import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Redirector {
    private static final String DEFAULT_URL = "http://default.com";
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public static void main(String[] args) {
        String targetUrl = "http://example.com/somepath";
        System.out.println(getRedirectUrl(targetUrl));
    }

    public static String getRedirectUrl(String url) {
        Matcher matcher = REDIRECT_PATTERN.matcher(url);
        return matcher.matches() ? url : DEFAULT_URL;
    }
}