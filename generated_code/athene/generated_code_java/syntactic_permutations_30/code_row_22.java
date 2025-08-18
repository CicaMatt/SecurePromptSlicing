import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RegexMatcher {
    public static void main(String[] args) {
        String target = "123-abc.";
        String regex = "^[a-zA-Z0-9\\-]+\\.";

        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(target);

        if (matcher.matches()) {
            System.out.println("Match found: " + target);
        } else {
            System.out.println("No match found.");
        }
    }
}