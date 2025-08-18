import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public String handleRedirect(String targetUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return "http://default-redirect.com";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.handleRedirect("https://example.com/page1"));
        System.out.println(handler.handleRedirect("http://anotherdomain.com/page2"));
    }
}