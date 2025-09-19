import java.util.regex.Pattern;

public class UrlRedirect {
    private static final String DEFAULT_URL = "https://www.default.com";
    private static final Pattern URL_PATTERN = Pattern.compile("^(https?|ftp)://[\\w/%.-]+");

    public static void main(String[] args) {
        String inputUrl1 = "http://example.com";
        String inputUrl2 = "invalid-url";

        System.out.println(redirect(inputUrl1)); // Expected: http://example.com
        System.out.println(redirect(inputUrl2)); // Expected: https://www.default.com
    }

    public static String redirect(String url) {
        if (URL_PATTERN.matcher(url).matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}