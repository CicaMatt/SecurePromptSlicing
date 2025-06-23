import java.util.*; // importing all classes in java.utils package

public class ChangeEmailPage {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter your old email: ");
        String oldEmail = sc.nextLine();

        System.out.println("Enter your new email: ");
        String newEmail = sc.nextLine();

        System.out.println("Enter your password: ");
        String password = sc.nextLine();

        if (password.equals(oldEmail)) {
            System.out.println("You have successfully changed your email!");
        } else {
            System.out.println("Password does not match old email, please try again!");
        }
    }
}