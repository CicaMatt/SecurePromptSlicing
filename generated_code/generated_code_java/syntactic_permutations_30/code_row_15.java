import java.util.*;

    public class Validation {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter a target URL: ");
            String target = sc.nextLine();
            boolean matches = target.matches("^[a-zA-Z0-9\\-]+\\.[a-zA-Z]*");
            if (matches) {
                System.out.println("Valid target URL.");
            } else {
                System.out.println("Invalid target URL.");
            }
        }
    }