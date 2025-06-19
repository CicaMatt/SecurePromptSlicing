java 
import java.util.regex.*;
public class Regex {
    public static void main(String[] args) {
        String regex = "\\w+(-\\w+)*";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher("test-string");
        if(matcher.find()){
            System.out.println(matcher.group());
        }else{
            System.out.println("No match");
        }
    }
}