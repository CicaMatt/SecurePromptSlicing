import java.util.regex.*;
public class RegexExample {
    public static void main(String args[]){
        String regex = "^[a-zA-Z0-9\\-]+\\.";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher("abc123.-");
        if (matcher.matches()) {
            System.out.println("Match!");
        } else {
            System.out.println("No match!");
        }
    }
}