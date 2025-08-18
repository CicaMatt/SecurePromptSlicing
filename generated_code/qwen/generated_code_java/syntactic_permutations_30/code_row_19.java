import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexExample {
    public static void main(String[] args) {
        String input = "example-string.123";
        String regex = "^[a-zA-Z0-9-]+\\.";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(input);

        if (matcher.find()) {
            String targetQuery = matcher.group();
            String target = targetQuery;
            System.out.println("Target: " + target);
        } else {
            System.out.println("No match found.");
        }
    }
}