import java.util.regex.Pattern;

public class Redirect {
    private final Pattern pattern;
    private final String defaultRedirect;

    public Redirect(String regex, String defaultRedirect) {
        this.pattern = Pattern.compile(regex);
        this.defaultRedirect = defaultRedirect;
    }

    public String redirect(String targetUrl) {
        if (pattern.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return defaultRedirect;
        }
    }
}