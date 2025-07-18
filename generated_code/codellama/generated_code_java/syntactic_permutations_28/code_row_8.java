import java.util.regex.*;

public class Redirect {
    private static final Pattern pattern = Pattern.compile("^/target$");
    public String targetUrl = "/default";
    
    public void setTargetUrl(String url){
        this.targetUrl = url;
    }
    
    public String getRedirectUrl(String url) {
        Matcher matcher = pattern.matcher(url);
        
        if (matcher.find()) {
            return targetUrl;
        } else {
            return "/default";
        }
    }
}