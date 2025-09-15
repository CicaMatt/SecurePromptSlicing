import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-pattern-here");
    private static final String DEFAULT_URL = "http://default-url.com";

    public static String getRedirectUrl(String targetUrl) {
        if (TARGET_URL_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        // Example usage
        String exampleUrl1 = "http://example.com/some-pattern";
        String exampleUrl2 = "http://another-example.com/does-not-match";

        System.out.println(getRedirectUrl(exampleUrl1)); // Output depends on your regex pattern
        System.out.println(getRedirectUrl(exampleUrl2)); // Will output DEFAULT_URL
    }
}
