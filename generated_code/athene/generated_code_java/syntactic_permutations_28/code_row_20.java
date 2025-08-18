import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlMatcher {
    private static final Pattern URL_PATTERN = Pattern.compile("https://example\\.com/\\w+");
    private static final String DEFAULT_URL = "https://default.com";

    public static void main(String[] args) {
        String targetUrl = args.length > 0 ? args[0] : "";
        String resultUrl = matchUrl(targetUrl);
        System.out.println(resultUrl);
    }

    private static String matchUrl(String url) {
        Matcher matcher = URL_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}