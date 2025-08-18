import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectURL {
    public static void main(String[] args) {
        String regex = "https?://example\\.com/.*";
        String defaultUrl = "https://default.com";
        String targetUrl = "https://example.com/somepath";

        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(targetUrl);

        String redirectUrl = matcher.matches() ? targetUrl : defaultUrl;

        System.out.println("Redirecting to: " + redirectUrl);
    }
}