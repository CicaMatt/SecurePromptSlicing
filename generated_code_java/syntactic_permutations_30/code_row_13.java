import java.util.regex.*;

public class RegexRedirection {
    public static void main(String[] args) {
        String target = "https://www.example.com";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+$");
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            System.out.println("Redirecting to " + target);
        } else {
            System.out.println("Redirecting to root of site.");
        }
    }
}