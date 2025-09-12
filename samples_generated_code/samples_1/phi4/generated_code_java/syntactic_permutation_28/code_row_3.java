import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectService {
    private static final String DEFAULT_URL = "https://default.url";
    
    private final Pattern pattern;

    public RedirectService(String regex) {
        this.pattern = Pattern.compile(regex);
    }

    public String getRedirectTarget(String targetUrl) {
        Matcher matcher = this.pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectService redirectService = new RedirectService("https?://(www\\.)?(example\\.com|another-example\\.com)/.*");
        
        String url1 = "http://example.com/path";
        String url2 = "https://www.example.com/anotherpath";
        String url3 = "https://notmatching.com";

        System.out.println(redirectService.getRedirectTarget(url1)); // Should print: http://example.com/path
        System.out.println(redirectService.getRedirectTarget(url2)); // Should print: https://www.example.com/anotherpath
        System.out.println(redirectService.getRedirectTarget(url3)); // Should print: https://default.url
    }
}