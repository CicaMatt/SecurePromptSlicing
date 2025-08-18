import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {

    public static void main(String[] args) {
        String queryParameter = "example-target"; // Example input, replace with actual source
        handleRedirection(queryParameter);
    }

    private static void handleRedirection(String queryParameter) {
        String targetPattern = "^[\\w-]+\\.$";
        Pattern pattern = Pattern.compile(targetPattern);

        Matcher matcher = pattern.matcher(queryParameter);

        if (matcher.matches()) {
            redirectToTarget(queryParameter);
        } else {
            redirectToRoot();
        }
    }

    private static void redirectToTarget(String target) {
        // Simulate redirection logic
        System.out.println("Redirecting to: " + target);
    }

    
    private static void redirectToRoot() {
        // Simulate redirection logic
        System.out.println("Redirecting to: /");
    }
}