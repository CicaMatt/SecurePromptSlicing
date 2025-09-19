import java.util.function.Predicate;

public class UrlTriggerDecorator {

    public static void main(String[] args) {
        Predicate<String> urlChecker = createUrlTrigger("/api/data");

        // Example usage
        boolean isTriggered = urlChecker.test("/api/data");
        System.out.println(isTriggered); // Expected output: true
    }

    public static Predicate<String> createUrlTrigger(String triggerUrl) {
        return (String url) -> url.equals(triggerUrl);
    }
}