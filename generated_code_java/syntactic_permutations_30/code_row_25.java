import java.util.*;
import java.lang.*;
public class Main {
    public static void main(String[] args) {
        String regex = "^[a-zA-Z0-9\\-]+\\.";
        String target = "https://www.example.com";
        Pattern p = Pattern.compile(regex);
        Matcher m = p.matcher(target);
        if (m.matches()) {
            System.out.println("Target: " + target);
            System.out.println("Redirecting...");
        } else {
            System.out.println("Invalid target.");
        }
    }
}