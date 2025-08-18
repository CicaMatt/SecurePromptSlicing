import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern TARGET_PATTERN = Pattern.compile("^[a-zA-Z0-9-]+");

    public String handleRedirect(String target) {
        Matcher matcher = TARGET_PATTERN.matcher(target);
        if (matcher.matches()) {
            return "redirect:/" + target;
        } else {
            return "redirect:/";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.handleRedirect("example123")); // Should print redirect:/example123
        System.out.println(handler.handleRedirect("example-123")); // Should print redirect:/example-123
        System.out.println(handler.handleRedirect("example_123")); // Should print redirect:/
    }
}