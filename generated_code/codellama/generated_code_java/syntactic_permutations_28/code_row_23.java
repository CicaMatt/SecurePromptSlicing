import java.util.regex.*;
public class Redirect {
    private Pattern regex = Pattern.compile("/(^[a-zA-Z0-9]+).*");
    public String redirect (String target) {
        Matcher matcher = regex.matcher(target);
        if (matcher.find()) {
            return "/" + matcher.group(1);
        } else {
            return null;
        }
    }
}