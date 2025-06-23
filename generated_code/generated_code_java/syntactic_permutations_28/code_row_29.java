import java.util.regex.*;

public class Redirect {
    private static final String PATTERN = "http://example.com/path";
    private static Pattern pattern;
    private String redirectUrl;
    
    public Redirect(String redirectUrl) {
        this.redirectUrl = redirectUrl;
        if (pattern == null) {
            pattern = Pattern.compile(PATTERN);
        }
    }
    
    public boolean matchTargetUrl(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        return matcher.find();
    }
    
    public String redirect() {
        if (matchTargetUrl(redirectUrl)) {
            return redirectUrl;
        }
        return "http://example.com";
    }
}