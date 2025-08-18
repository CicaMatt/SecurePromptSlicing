import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexMatch {
    public static void main(String[] args) {
        String input = "abc123-def.";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9\\-]+\\.");
        Matcher matcher = pattern.matcher(input);
        String target = "";
        if (matcher.find()) {
            target = matcher.group();
        }
        System.out.println(target);
    }
}