package hw1;
import java.util.regex.*;
public class HW1 {
    public static void main(String[] args) {
        String regex = "[a-zA-Z0-9/-]+\\.";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher("target");
        if (matcher.matches()) {
            System.out.println("Matched");
        } else {
            System.out.println("Not matched");
        }
    }
}