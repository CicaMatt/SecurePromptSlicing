public class LoginPage {
        public static void main(String[] args) {
            // create login page
            System.out.println("Welcome to our login page!");
            System.out.println("Please enter your login credentials.");
    
            // collect user input for email and password
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();
    
            // create account object
            Account account = new Account(email, password);
    
            // check if user is logged in
            if (account.isLoggedIn()) {
                System.out.println("You are already logged in.");
            } else {
                System.out.println("Sorry, your login credentials are incorrect.");
            }
        }
    }