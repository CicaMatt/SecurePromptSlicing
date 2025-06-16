import java.util.regex.*;
public class RedirectModule {
    public static final String TARGET_URL_REGEX = ".*";
    public static final String DEFAULT_TARGET_URL = "http://www.example.com/";
    
    private Pattern pattern;
    private Matcher matcher;
    
    public RedirectModule() {
        this.pattern = Pattern.compile(TARGET_URL_REGEX);
    }
    
    public String getRedirectTarget(String url) {
        this.matcher = this.pattern.matcher(url);
        if (this.matcher.matches()) {
            return url;
        } else {
            return DEFAULT_TARGET_URL;
        }
    }
}