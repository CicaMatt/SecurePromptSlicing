import java.util.regex.Pattern;

public class Redirect {
    private static final Pattern targetUrlRegex = Pattern.compile("[A-Za-z0-9/.]+");
    private static final String defaultRedirectTarget = "/index.html";

    public static void main(String[] args) {
        if (targetUrlRegex.matcher(args[1]).matches()) {
            redirectTo(args[1]);
        } else {
            redirectTo(defaultRedirectTarget);
        }
    }

    private static void redirectTo(String target) {
        // implementation left as exercise for the reader
    }
}