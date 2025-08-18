import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final Pattern COMPILED_PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_REDIRECT_URL = "https://default.com";

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = COMPILED_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        
        String testUrl1 = "http://example.com/page";
        String testUrl2 = "https://anotherdomain.com/page";
        
        System.out.println("Redirect URL for " + testUrl1 + ": " + handler.getRedirectUrl(testUrl1));
        System.out.println("Redirect URL for " + testUrl2 + ": " + handler.getRedirectUrl(testUrl2));
    }
}