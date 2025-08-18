import java.util.regex.Pattern;

public class URLRedirector {

    private static final String DEFAULT_URL = "https://default.example.com";
    private static final Pattern URL_PATTERN = Pattern.compile("http[s]?://example\\.com/(.*)");

    public static void main(String[] args) {
        String targetURL = "http://example.com/path/to/resource";

        String redirectTarget = getRedirectTarget(targetURL);
        System.out.println(redirectTarget);
    }

    private static String getRedirectTarget(String targetURL) {
        if (URL_PATTERN.matcher(targetURL).matches()) {
            return targetURL;
        } else {
            return DEFAULT_URL;
        }
    }
}