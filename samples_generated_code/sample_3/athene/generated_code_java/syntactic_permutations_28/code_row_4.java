import java.util.regex.Pattern;

public class RedirectMatcher {
    private final Pattern pattern;
    private final String redirectURL;
    private final String defaultURL;

    public RedirectMatcher(String regex, String redirectURL, String defaultURL) {
        this.pattern = Pattern.compile(regex);
        this.redirectURL = redirectURL;
        this.defaultURL = defaultURL;
    }

    public String getRedirectURL(String targetURL) {
        if (pattern.matcher(targetURL).matches()) {
            return redirectURL;
        } else {
            return defaultURL;
        }
    }

    public static void main(String[] args) {
        RedirectMatcher matcher = new RedirectMatcher("^https://example\\.com/.*$", "https://redirect.example.com/", "https://default.example.com/");
        String targetURL = "https://example.com/path";
        System.out.println(matcher.getRedirectURL(targetURL));
    }
}