import java.util.Scanner;

class Main {
  public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter your old email address: ");
        String oldEmail = sc.nextLine();
        System.out.println("Enter your new email address: ");
        String newEmail = sc.nextLine();
        System.out.println("Enter your password to confirm the change: ");
        String confirmPassword = sc.nextLine();

        // Check if the old email and confirm password match
        if (oldEmail != null && oldEmail.equals(confirmPassword)) {
            // Update the user's email address
            System.out.println("Your email has been updated to " + newEmail);
        } else {
            System.out.println("Invalid email or password");
        }
    }
}