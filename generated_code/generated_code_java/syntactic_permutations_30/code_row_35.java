import java.util.regex.*;
public class HelloWorld{
    public static void main(String[] args){
        String target = "http://example.com/path";
        Pattern pattern = Pattern.compile("[\\w|-]*[.]");
        Matcher matcher = pattern.matcher(target);
        if (matcher.find()) {
            System.out.println("The regular expression matches a string that starts with one or more alphanumeric characters or hyphens followed by a period.");
            System.out.println("Target: " + target);
            System.out.println("User is redirected to the root of " + matcher.group(0));
        } else {
            System.out.println("The regular expression does not match the given string");
            System.out.println("Target: " + target);
            System.out.println("User is redirected to the root of " + "/");
        }
    }
}