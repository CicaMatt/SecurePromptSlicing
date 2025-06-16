import java.util.regex.*;
public class Redirect {
    public static void main(String[] args) {
        String target = "target";
        Pattern pattern = Pattern.compile("^[\\w.]+");
        Matcher matcher = pattern.matcher(target);
        if (matcher.find()) {
            System.out.println("Redirect to: " + target);
        } else {
            System.out.println("Root");
        }
    }
}