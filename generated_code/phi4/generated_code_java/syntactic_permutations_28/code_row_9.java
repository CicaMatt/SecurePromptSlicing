import java.net.URL;
import java.util.regex.Pattern;

public class RedirectHandler {

    private static final Pattern TARGET_PATTERN = Pattern.compile("your-regex-here");
    private static final String DEFAULT_URL = "http://default.url";

    public String getRedirectURL(String targetURL) {
        if (TARGET_PATTERN.matcher(targetURL).matches()) {
            return targetURL;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) throws Exception {
        RedirectHandler handler = new RedirectHandler();
        
        // Example usage
        String url1 = "http://example.com/target";
        String url2 = "http://example.com/other";

        System.out.println(handler.getRedirectURL(url1));  // Output depends on regex match
        System.out.println(handler.getRedirectURL(url2));  // Should output DEFAULT_URL if not matching
    }
}
