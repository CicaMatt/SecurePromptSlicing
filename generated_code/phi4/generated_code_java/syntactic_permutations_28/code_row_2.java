import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectUrlMatcher {

    private static final String DEFAULT_URL = "http://default.url";
    private final Pattern pattern;

    public RedirectUrlMatcher(String regex) {
        this.pattern = Pattern.compile(regex);
    }

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        }
        return DEFAULT_URL;
    }

    public static void main(String[] args) {
        RedirectUrlMatcher redirectMatcher = new RedirectUrlMatcher("https?://(www\\.)?example\\.com/.*");
        
        String url1 = "http://example.com/page";
        String url2 = "http://notexample.com/page";

        System.out.println(redirectMatcher.getRedirectUrl(url1)); // Outputs: http://example.com/page
        System.out.println(redirectMatcher.getRedirectUrl(url2)); // Outputs: http://default.url
    }
}