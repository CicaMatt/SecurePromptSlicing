import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private final Pattern pattern;
    private final String defaultUrl;
    private final String redirectUrlTemplate;

    public RedirectHandler(String regex, String defaultUrl, String redirectUrlTemplate) {
        this.pattern = Pattern.compile(regex);
        this.defaultUrl = defaultUrl;
        this.redirectUrlTemplate = redirectUrlTemplate;
    }

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return redirectUrlTemplate; // Since no dynamic construction is required, we return the template as-is.
        } else {
            return defaultUrl;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler("https://example\\.com/.*", "https://default.com", "https://redirect.com");
        
        String testUrl1 = "https://example.com/some/path";
        String testUrl2 = "https://another-example.com/some/path";

        System.out.println(handler.getRedirectUrl(testUrl1)); // Should print: https://redirect.com
        System.out.println(handler.getRedirectUrl(testUrl2)); // Should print: https://default.com
    }
}