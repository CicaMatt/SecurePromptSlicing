import java.util.*;
import java.util.regex.*;
import com.google.common.collect.ImmutableList;
public class RedirectRule {
    private final String regexp;
    private final Pattern pattern;
    private final String defaultUrl;
    public RedirectRule(String regexp, String defaultUrl) {
        this.regexp = regexp;
        this.pattern = Pattern.compile(regexp);
        this.defaultUrl = defaultUrl;
    }
    public String applyTo(String url) {
        if (this.pattern.matcher(url).matches()) {
            return url;
        } else {
            return this.defaultUrl;
        }
    }
}
RedirectRule rule = new RedirectRule("https://example\\.com/.*", "https://www\\.example\\.com/");
System.out.println(rule.applyTo("http://example.com"));   // https://www.example.com/