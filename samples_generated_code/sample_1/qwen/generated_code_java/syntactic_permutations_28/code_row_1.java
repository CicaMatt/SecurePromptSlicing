import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectModule {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        }
        return null; // or handle accordingly
    }

    public static void main(String[] args) {
        RedirectModule module = new RedirectModule();
        String url1 = "http://example.com/somepath";
        String url2 = "https://anotherdomain.com/path";

        System.out.println("Redirect URL for " + url1 + ": " + module.getRedirectUrl(url1));
        System.out.println("Redirect URL for " + url2 + ": " + module.getRedirectUrl(url2));
    }
}