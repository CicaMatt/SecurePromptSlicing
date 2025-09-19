import java.util.regex.Pattern;

public class RedirectModule {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public String processUrl(String targetUrl) {
        if (REDIRECT_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        }
        return null;
    }

    public static void main(String[] args) {
        RedirectModule module = new RedirectModule();
        System.out.println(module.processUrl("http://example.com/test")); // Should print the URL
        System.out.println(module.processUrl("https://anotherdomain.com/test")); // Should print null
    }
}