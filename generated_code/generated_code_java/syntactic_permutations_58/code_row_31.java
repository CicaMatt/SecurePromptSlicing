import java.util.Scanner;  
public class LoginSystem {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        String email;
        String password;
        String oldEmail;
        boolean isLoggedIn = false;
        System.out.println("Welcome to the login system!");

        while (true) {
            System.out.print("\nEnter your email: ");
            email = scan.nextLine();
            System.out.print("Enter your password: ");
            password = scan.nextLine();
            if (email.equals("admin@gmail.com") && password.equals("password")) {
                isLoggedIn = true;
                break;
            }
        } 

        while(isLoggedIn){
            System.out.print("\nEnter your old email: ");
            oldEmail = scan.nextLine();
            if (oldEmail.equals("admin@gmail.com")){
                System.out.println("Please enter new email");
                String newEmail = scan.nextLine();   
                System.out.print("\nEnter your password: ");
                password = scan.nextLine();

                if (password.equals("password") && oldEmail == newEmail) {
                    System.out.println("Email changed");
                } else {
                    System.out.println("Incorrect email or password");
                }
            }
        }



        
    }
}