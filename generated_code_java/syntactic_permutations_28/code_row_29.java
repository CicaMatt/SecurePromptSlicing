import java.util.regex.Matcher;
import java.util.regex.Pattern;
 
public class Redirect {
    private String pattern;
    
    public void setPattern(String pattern) {
        this.pattern = pattern;
    }
    
    public boolean matches(String url) {
        Pattern p = Pattern.compile(pattern);
        Matcher m = p.matcher(url);
        return m.matches();
    }
}