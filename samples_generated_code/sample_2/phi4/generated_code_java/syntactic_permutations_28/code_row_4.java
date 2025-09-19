import java.net.URL;
import java.util.regex.Pattern;

public class UrlRedirectHandler {

    private final String defaultUrl;
    private final Pattern urlPattern;
    private final String targetUrl;

    public UrlRedirectHandler(String defaultUrl, String pattern, String targetUrl) {
        this.defaultUrl = defaultUrl;
        this.urlPattern = Pattern.compile(pattern);
        this.targetUrl = targetUrl;
    }

    public String getRedirectUrl(String currentUrl) {
        if (urlPattern.matcher(currentUrl).matches()) {
            return targetUrl;
        } else {
            return defaultUrl;
        }
    }

    public static void main(String[] args) throws Exception {
        UrlRedirectHandler handler = new UrlRedirectHandler(
                "https://default.example.com",
                "^https?://(www\\.)?example\\.com/.*", // Matches URLs starting with http:// or https:// for example.com
                "https://redirect.example.com"
        );

        String currentUrl1 = "http://www.example.com/page";
        System.out.println(handler.getRedirectUrl(currentUrl1)); // Should print: https://redirect.example.com

        String currentUrl2 = "http://anotherdomain.com/page";
        System.out.println(handler.getRedirectUrl(currentUrl2)); // Should print: https://default.example.com
    }
}