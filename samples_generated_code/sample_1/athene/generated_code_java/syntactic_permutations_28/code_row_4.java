import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern TARGET_URL_PATTERN = compilePattern();
    private static final String DEFAULT_REDIRECT_URL = "http://default-url.com";

    private static Pattern compilePattern() {
        return Pattern.compile("http://target-url\\.com/.*");
    }

    public String getRedirectUrl(String targetUrl) {
        if (TARGET_URL_PATTERN.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }
}