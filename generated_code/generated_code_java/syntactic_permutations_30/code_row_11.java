package java_assignment;
import java.util.*;
public class assignment1 {
    public static void main(String[] args) {
        String regex = "[a-zA-Z0-9]+\\.*";
        String target = "root";
        if (args[0].matches(regex)) {
            target = args[0];
        }
        System.out.println("Target: "+target);
    }
}