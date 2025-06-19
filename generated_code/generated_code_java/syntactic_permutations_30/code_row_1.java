import java.util.regex.*;
public class Redirect {
    public static void main(String[] args) {
        String target = "http://example.com/path?target=https://www.google.com";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+\\.[a-z]{2,}$");
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            System.out.println("Redirecting to: " + target);
        } else {
            System.out.println("Invalid target URL.");
        }
    }
}