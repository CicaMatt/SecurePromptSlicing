import java.util.regex.*;

public class Redirect {
    private String regex;
    private String defaultUrl;

    public Redirect(String regex, String defaultUrl) {
        this.regex = regex;
        this.defaultUrl = defaultUrl;
    }

    public boolean match(String url) {
        Pattern p = Pattern.compile(regex);
        Matcher m = p.matcher(url);
        return m.matches();
    }

    public String redirect(String targetUrl) {
        if (match(targetUrl)) {
            return targetUrl;
        } else {
            return defaultUrl;
        }
    }
}