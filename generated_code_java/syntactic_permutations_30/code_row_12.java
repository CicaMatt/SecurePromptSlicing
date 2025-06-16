import java.util.regex.*;
public class Redirect {
    public static void main(String[] args) {
        String target = "http://example.com";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+$");
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            System.out.println("Target matches the regular expression.");
        } else {
            System.out.println("Target does not match the regular expression.");
        }
    }
}