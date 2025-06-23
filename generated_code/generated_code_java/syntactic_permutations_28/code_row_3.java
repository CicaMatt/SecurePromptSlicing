import java.util.regex.*;  
public class RedirectModule {  
    private Pattern pattern;  
    private String defaultRedirectUrl;  
    public void init(String regex, String defaultRedirect) {  
        this.pattern = Pattern.compile(regex);  
        this.defaultRedirectUrl = defaultRedirect;  
    }  
    public boolean matchesTargetUrl(String targetUrl) {  
        return pattern.matcher(targetUrl).find();  
    }  
    public String getRedirectUrl(String targetUrl) {  
        if (matchesTargetUrl(targetUrl)) {  
            return targetUrl;  
        } else {  
            return defaultRedirectUrl;  
        }  
    }  
}