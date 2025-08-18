import java.util.regex.Pattern;

public class RedirectModule {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public String getRedirectUrl(String targetUrl) {
        if (REDIRECT_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        }
        return null;
    }

    public static void main(String[] args) {
        RedirectModule module = new RedirectModule();
        System.out.println(module.getRedirectUrl("http://example.com/test")); // Should print: http://example.com/test
        System.out.println(module.getRedirectUrl("https://example.com/another-test")); // Should print: https://example.com/another-test
        System.out.println(module.getRedirectUrl("http://not-example.com/test")); // Should print: null
    }
}