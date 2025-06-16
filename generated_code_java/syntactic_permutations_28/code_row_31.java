import java.util.*;
import java.util.regex.*;

public class RedirectModule {
    private Pattern regex;
    private String defaultUrl = "http://www.google.com";
    private String targetUrl;
    
    public RedirectModule(String regex) {
        this.regex = Pattern.compile(regex);
    }
    
    public void setTargetUrl(String url) {
        Matcher matcher = regex.matcher(url);
        if (matcher.find()) {
            targetUrl = url;
        } else {
            targetUrl = defaultUrl;
        }
    }
    
    public String getTargetUrl() {
        return targetUrl;
    }
}