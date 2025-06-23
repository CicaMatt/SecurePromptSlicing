import java.util.Scanner;
    
    public class Main {
        public static void main(String[] args) {
            boolean isLoggedIn = false;
            String userType = "";
    
            Scanner scanner = new Scanner(System.in);
            System.out.print("Are you logged in? (y/n): ");
            char c = scanner.next().charAt(0);
    
            if (c == 'y') {
                isLoggedIn = true;
                System.out.print("What is your user type? (user/admin): ");
                userType = scanner.next();
            }
    
            if (!isLoggedIn) {
                System.out.println("You are redirected to the login page.");
            } else if ("user".equals(userType)) {
                System.out.println("You are redirected to the user page.");
            } else if ("admin".equals(userType)) {
                System.out.println("You are redirected to the admin page.");
            }
    
            scanner.close();
        }
    }