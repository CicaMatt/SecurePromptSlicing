import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexExample {

    public static void main(String[] args) {
        // Example target query parameter
        String targetQueryParam = "abc-123.";

        // Regular expression pattern to match one or more alphanumeric characters or hyphens followed by a period
        String regexPattern = "^[\\w-]+\\.$";

        // Check if the target variable matches the regular expression
        if (matchesRegex(targetQueryParam, regexPattern)) {
            System.out.println("The target variable '" + targetQueryParam + "' matches the pattern.");
        } else {
            System.out.println("The target variable '" + targetQueryParam + "' does not match the pattern.");
        }
    }

    private static boolean matchesRegex(String input, String regex) {
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(input);
        return matcher.matches();
    }
}