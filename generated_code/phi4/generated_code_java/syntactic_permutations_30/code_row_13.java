import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectExample {
    public static void main(String[] args) {
        String target = System.getProperty("target");
        
        if (target == null || !isValidTarget(target)) {
            redirectToRoot();
        } else {
            redirectToTarget(target);
        }
    }

    private static boolean isValidTarget(String target) {
        Pattern pattern = Pattern.compile("^[\\w-]+$");
        Matcher matcher = pattern.matcher(target);
        return matcher.matches();
    }

    private static void redirectToTarget(String target) {
        System.out.println("Redirecting to: /" + target);
        // Implement actual redirection logic here
    }

    private static void redirectToRoot() {
        System.out.println("Redirecting to: /");
        // Implement actual redirection logic here
    }
}