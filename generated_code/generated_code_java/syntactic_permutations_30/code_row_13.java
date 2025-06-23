import java.util.regex.*;
public class Test {
    public static void main(String args[]){
        String regex = "[a-zA-Z0-9-]+";
        Pattern p = Pattern.compile(regex);
        String target = "http://example.com";
        Matcher m = p.matcher(target);
        if (m.find()) {
            // do something here, maybe redirect the user to the target?
            System.out.println("Successful match");
        } else {
            // no match, redirect to root of site
            System.out.println("Unsuccessful match");
        }
    }
}