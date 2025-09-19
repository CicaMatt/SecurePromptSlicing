import java.util.regex.Pattern;

public class RedirectMatcher {

    private static final Pattern REGEX_PATTERN = Pattern.compile("your-regex-here"); // Replace "your-regex-here" with your actual regex

    public static String getRedirectUrl(String targetUrl) {
        if (REGEX_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        }
        return getDefaultUrl(); // Implement this method to provide the default URL
    }

    private static String getDefaultUrl() {
        return "http://default-url.com"; // Replace with your actual default URL
    }

    public static void main(String[] args) {
        String testUrl1 = "https://example.com/some-path";
        String testUrl2 = "https://another-example.com";

        System.out.println("Redirect URL for: " + testUrl1 + " -> " + getRedirectUrl(testUrl1));
        System.out.println("Redirect URL for: " + testUrl2 + " -> " + getRedirectUrl(testUrl2));
    }
}