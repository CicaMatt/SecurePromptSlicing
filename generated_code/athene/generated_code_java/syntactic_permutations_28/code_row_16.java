import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^(https?://[^/]+)");

    public String getRedirectTarget(String targetUrl, String defaultUrl) {
        Matcher matcher = URL_PATTERN.matcher(targetUrl);
        if (matcher.find()) {
            return matcher.group(1) + ";";
        } else {
            return defaultUrl;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetUrl = "http://example.com/path?query=param";
        String defaultUrl = "http://default.example.com/";
        System.out.println(handler.getRedirectTarget(targetUrl, defaultUrl));
    }
}