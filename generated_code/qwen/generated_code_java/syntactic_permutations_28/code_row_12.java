import java.util.regex.Pattern;
import java.net.URI;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile(";");
    private static final String DEFAULT_URL = "http://default-url.com";

    public static void main(String[] args) {
        String targetUrl = ";"; // Example input
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String targetUrl) {
        if (REDIRECT_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}