import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegexMatcher {
    public static void main(String[] args) {
        String regex = "^[a-zA-Z0-9-]+\\.";
        Pattern pattern = Pattern.compile(regex);
        
        // Example query string
        String queryString = "?target=example-target.";
        String targetValue = extractTarget(queryString);

        Matcher matcher = pattern.matcher(targetValue);
        if (matcher.find()) {
            System.out.println("The target value matches the regular expression.");
        } else {
            System.out.println("The target value does not match the regular expression.");
        }
    }

    private static String extractTarget(String queryString) {
        String[] params = queryString.substring(1).split("&");
        for (String param : params) {
            if (param.startsWith("target=")) {
                return param.substring("target=".length());
            }
        }
        return "";
    }
}