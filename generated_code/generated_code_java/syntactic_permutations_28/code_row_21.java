import java.util.regex.Pattern;
import java.util.regex.Matcher;
public class RedirectRule{
    private Pattern pattern;
    public RedirectRule(String regex){
        this.pattern = Pattern.compile(regex);
    }
    public boolean matches(String targetUrl){
        Matcher matcher = pattern.matcher(targetUrl);
        return matcher.matches();
    }
}