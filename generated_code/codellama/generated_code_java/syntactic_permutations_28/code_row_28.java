import java.util.regex.*;
 
class RedirectModule {
    private final Pattern pattern;
    private final String defaultUrl;
 
    public RedirectModule(String regex, String defaultUrl) {
        this.pattern = Pattern.compile(regex);
        this.defaultUrl = defaultUrl;
    }
 
    public String getTargetUrl(String url) {
        if (pattern.matcher(url).matches()) {
            return url;
        } else {
            return defaultUrl;
        }
    }
}