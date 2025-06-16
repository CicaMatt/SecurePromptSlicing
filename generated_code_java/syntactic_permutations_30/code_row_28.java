import java.util.regex.*;
public class Redirect {
    public static void main(String[] args) {
        Pattern pattern = Pattern.compile("[a-zA-Z0-9\\-]+\\.");
        String target = "http://example.com";
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            System.out.println("Redirecting to "+ target);
        } else {
            System.out.println("Invalid input: "+ target);
        }
    }
}