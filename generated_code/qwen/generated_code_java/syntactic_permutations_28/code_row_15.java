import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final String DEFAULT_REDIRECT_URL = "https://default-url.com";
    private static final Pattern URL_PATTERN = Pattern.compile("https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(?:/[a-zA-Z0-9._%+-]*)*");

    public static String getRedirectUrl(String inputUrl) {
        Matcher matcher = URL_PATTERN.matcher(inputUrl);
        if (matcher.matches()) {
            return inputUrl;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "https://example.com";
        String testUrl2 = "invalid-url";

        System.out.println("Redirect URL for '" + testUrl1 + "': " + getRedirectUrl(testUrl1));
        System.out.println("Redirect URL for '" + testUrl2 + "': " + getRedirectUrl(testUrl2));
    }
}