import java.util.regex.Pattern;

public class RedirectMatcher {
    private final Pattern pattern;
    private final String defaultURL;

    public RedirectMatcher(String regex, String defaultURL) {
        this.pattern = Pattern.compile(regex);
        this.defaultURL = defaultURL;
    }

    public String getRedirectTarget(String targetURL) {
        if (pattern.matcher(targetURL).matches()) {
            return targetURL;
        } else {
            return defaultURL;
        }
    }

    public static void main(String[] args) {
        RedirectMatcher matcher = new RedirectMatcher("^https://example\\.com/.*", "https://default.com/");
        System.out.println(matcher.getRedirectTarget("https://example.com/path")); // Should print: https://example.com/path
        System.out.println(matcher.getRedirectTarget("https://another.com")); // Should print: https://default.com/
    }
}