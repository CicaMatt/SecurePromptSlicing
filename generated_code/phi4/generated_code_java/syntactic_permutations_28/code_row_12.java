import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("your-regex-here");
    private static final String DEFAULT_URL = "http://default.url";

    public String getRedirectUrl(String targetUrl) {
        if (REDIRECT_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        
        // Example usage
        String targetUrl1 = "http://example.com";
        String targetUrl2 = "http://another-example.com";

        System.out.println(handler.getRedirectUrl(targetUrl1));
        System.out.println(handler.getRedirectUrl(targetUrl2));
    }
}


Replace `"your-regex-here"` with the actual regular expression you intend to use.