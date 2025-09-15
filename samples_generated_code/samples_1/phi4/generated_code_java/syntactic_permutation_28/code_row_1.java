import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {

    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-here");

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = TARGET_URL_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl; // Use the target URL as the redirect target.
        } else {
            return "default-url"; // Use a default URL if it does not match.
        }
    }

    public static void main(String[] args) {
        UrlRedirector urlRedirector = new UrlRedirector();
        
        String testUrl1 = "example-url-that-matches";
        System.out.println("Redirect URL for: " + testUrl1 + " is " + urlRedirector.getRedirectUrl(testUrl1));
        
        String testUrl2 = "example-url-that-does-not-match";
        System.out.println("Redirect URL for: " + testUrl2 + " is " + urlRedirector.getRedirectUrl(testUrl2));
    }
}
