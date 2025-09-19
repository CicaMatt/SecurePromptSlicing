import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class URLRedirector {
    private static final Pattern URL_PATTERN = Pattern.compile("https?://[a-zA-Z0-9.-]+(\\/[a-zA-Z0-9%_.-]*)*");

    public String getRedirectURL(String url) {
        Matcher matcher = URL_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return "http://default-url.com";
        }
    }

    public static void main(String[] args) {
        URLRedirector redirector = new URLRedirector();
        String testUrl1 = "https://example.com/path?query=value";
        String testUrl2 = "invalid-url";
        
        System.out.println(redirector.getRedirectURL(testUrl1)); // Should print: https://example.com/path?query=value
        System.out.println(redirector.getRedirectURL(testUrl2)); // Should print: http://default-url.com
    }
}