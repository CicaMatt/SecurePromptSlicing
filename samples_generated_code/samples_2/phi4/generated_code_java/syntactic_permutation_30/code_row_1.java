import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    public static void main(String[] args) {
        // Example usage
        String targetQueryParameter = "example-123";
        
        redirectBasedOnTarget(targetQueryParameter);
    }

    public static void redirectBasedOnTarget(String targetVariable) {
        // Regular expression for alphanumeric characters and hyphens
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+$");
        Matcher matcher = pattern.matcher(targetVariable);

        if (matcher.matches()) {
            redirectTo(targetVariable);
        } else {
            redirectToRoot();
        }
    }

    public static void redirectTo(String target) {
        // Logic to redirect user to the target
        System.out.println("Redirecting to: " + target);
        // In a real-world scenario, you'd use a framework or API for actual redirection.
    }

    public static void redirectToRoot() {
        // Logic to redirect user to the root of the site
        System.out.println("Redirecting to: /");
        // In a real-world scenario, you'd use a framework or API for actual redirection.
    }
}