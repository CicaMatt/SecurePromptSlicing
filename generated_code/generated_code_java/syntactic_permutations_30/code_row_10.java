import java.util.regex.*;

public class Redirect {
    public static void main(String[] args) {
        String target = "http://www.example.com";
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9]+$");
        Matcher matcher = pattern.matcher(target);
        
        if (matcher.matches()) {
            System.out.println("User is redirected to the target site.");
        } else {
            System.out.println("User is redirected to the root of the site.");
        }
    }
}