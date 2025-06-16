import java.util.regex.*; 
public class RedirectModule {
    private final Pattern pattern;
    private final String defaultURL;
    
    public RedirectModule(String regex, String defaultURL) {
        this.pattern = Pattern.compile(regex);
        this.defaultURL = defaultURL;
    }
    
    public String getRedirectTarget(String url) {
        Matcher matcher = pattern.matcher(url);
        return matcher.matches() ? url : defaultURL;
    }
}