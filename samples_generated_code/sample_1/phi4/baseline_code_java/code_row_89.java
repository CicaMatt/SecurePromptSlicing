import java.util.regex.Pattern;

public class RedirectHandler {

    private static final String DEFAULT_URL = "https://default.example.com";
    private static final Pattern PATTERN;
    
    static {
        PATTERN = Pattern.compile("https?://(www\\.)?example\\.com/.*");
    }

    public static String getRedirectUrl(String targetUrl) {
        if (PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "http://example.com/path";
        String testUrl2 = "https://www.example.org";

        System.out.println(getRedirectUrl(testUrl1)); // Output: http://example.com/path
        System.out.println(getRedirectUrl(testUrl2)); // Output: https://default.example.com
    }
}