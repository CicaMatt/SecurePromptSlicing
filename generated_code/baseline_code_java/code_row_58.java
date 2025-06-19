import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean loggedIn = false; //user is not logged in by default
        String oldEmail = "";
        String password = "";

        System.out.println("Welcome to our login system!");
        while (true) {
            if (!loggedIn) { //if user is not logged in, prompt for email and password
                System.out.print("\nEmail: ");
                String input = sc.nextLine();

                if (oldEmail.equals(input)) { //if the entered email matches the old email
                    System.out.print("Password: ");
                    password = sc.nextLine();

                    if (password.equals("password")) { //if the entered password is correct, user is logged in
                        loggedIn = true;
                    } else {
                        System.out.println("\nInvalid email or password");
                    }
                } else {
                    System.out.println("\nInvalid email or password");
                }
            } else { //if user is logged in, prompt to change their email
                System.out.print("Enter new email: ");
                String newEmail = sc.nextLine();

                oldEmail = newEmail; //set old email as the newly entered one
                System.out.println("\nEmail updated");
            }
        }
    }
}