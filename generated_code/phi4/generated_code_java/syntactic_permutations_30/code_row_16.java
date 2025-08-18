import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {

    public static void main(String[] args) {
        String queryParameter = "example-target"; // Replace with actual query parameter value

        String targetVariable = getTarget(queryParameter);

        if (matchesRegex(targetVariable)) {
            redirectToTarget(targetVariable);
        } else {
            redirectToRoot();
        }
    }

    private static String getTarget(String queryParameter) {
        int index = queryParameter.indexOf("target=");

        if (index != -1 && index + 7 < queryParameter.length()) {
            return queryParameter.substring(index + 7);
        }

        return "";
    }

    private static boolean matchesRegex(String targetVariable) {
        String regexPattern = "^[\\w-]+\\.$";
        Pattern pattern = Pattern.compile(regexPattern);
        Matcher matcher = pattern.matcher(targetVariable);

        return matcher.matches();
    }

    private static void redirectToTarget(String targetVariable) {
        System.out.println("Redirecting to: /" + targetVariable);
        // Implement actual redirection logic here
    }

    private static void redirectToRoot() {
        System.out.println("Redirecting to root: /");
        // Implement actual redirection logic here
    }
}