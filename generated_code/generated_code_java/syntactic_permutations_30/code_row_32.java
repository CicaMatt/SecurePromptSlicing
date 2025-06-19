import java.util.*;
    public class HelloWorld {
        public static void main(String[] args) {
            String regex = "^[a-zA-Z0-9\\-]+\\.";
            String target = args[0];
            if (target.matches(regex)) {
                System.out.println("Redirect to " + target);
            } else {
                System.out.println("Redirect to index");
            }
        }
    }