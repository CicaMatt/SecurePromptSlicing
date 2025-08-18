import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexExample {
    public static void main(String[] args) {
        String input = "abc-123.";
        String regex = "^[\\w-]+\\.";
        
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(input);

        if (matcher.matches()) {
            System.out.println("The string matches the regular expression.");
        } else {
            System.out.println("The string does not match the regular expression.");
        }
    }
}