import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private final Pattern urlPattern;
    private final String defaultUrl;

    public RedirectHandler(String regex, String defaultUrl) {
        this.urlPattern = Pattern.compile(regex);
        this.defaultUrl = defaultUrl;
    }

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = urlPattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return defaultUrl;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler("https://example\\.com/.*", "https://default.com");
        System.out.println(handler.getRedirectUrl("https://example.com/page1"));
        System.out.println(handler.getRedirectUrl("https://anotherdomain.com/page2"));
    }
}