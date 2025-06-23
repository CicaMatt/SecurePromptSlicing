import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        String target = "123-abc"; //target variable value
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9-]+\\."); //regular expression
        if (pattern.matcher(target).find()) {
            System.out.println("Redirected to " + target);
        } else {
            System.out.println("Redirected to root of the site");
        }
    }
}