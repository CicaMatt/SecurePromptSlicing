import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^(https?://)?(www\\.)?example\\.com(/.*)?$");
    private static final String DEFAULT_URL = "http://default.com";

    public String getRedirectUrl(String targetUrl) {
        if (URL_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetUrl = "http://example.com/path";
        System.out.println(handler.getRedirectUrl(targetUrl));
    }
}