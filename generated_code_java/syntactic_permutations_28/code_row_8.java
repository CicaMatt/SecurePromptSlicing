import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectModule {
    private String targetUrl;
    private String defaultUrl;
    private Pattern pattern;

    public RedirectModule(String targetUrl, String defaultUrl) {
        this.targetUrl = targetUrl;
        this.defaultUrl = defaultUrl;
        this.pattern = Pattern.compile("^\\w+://(\\d{1,3}\\.){3}\\d{1,3}(:\\d+)?(/.*)?$");
    }

    public String getRedirectTarget() {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return defaultUrl;
        }
    }
}