import java.util.Scanner;

public class EmailChange {
    private static String email;
    private static String newEmail;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email: ");
        email = scanner.nextLine();

        if (email.isEmpty()) {
            System.out.println("Please enter a valid email");
            main(args);
        } else {
            System.out.print("Enter new email: ");
            newEmail = scanner.nextLine();

            if (!isValidEmail(newEmail)) {
                System.out.println("Invalid email format.");
                main(args);
            } else if (email.equals(newEmail)) {
                System.out.println("New email cannot be the same as old email.");
                main(args);
            } else {
                System.out.print("Enter confirm password: ");
                String confirmPassword = scanner.nextLine();

                if (!isValidPassword(confirmPassword)) {
                    System.out.println("Invalid password format.");
                    main(args);
                } else if (confirmPassword.equals(newEmail)) {
                    System.out.println("Password cannot be the same as new email.");
                    main(args);
                } else {
                    String user = getUserFromEmail(email);
                    if (user == null) {
                        System.out.println("The provided email does not exist");
                        main(args);
                    } else {
                        if (!checkPassword(confirmPassword, user)) {
                            System.out.println("Invalid password for the provided email.");
                            main(args);
                        } else {
                            String oldEmail = email;
                            updateUserEmail(user, newEmail);
                            System.out.println("Successfully changed email from " + oldEmail + " to " + newEmail);
                        }
                    }
                }
            }
        }
    }

    private static boolean isValidEmail(String email) {
        return email.matches("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+$");
    }

    private static boolean isValidPassword(String password) {
        return password.matches("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9]).{8,}$");
    }

    private static String getUserFromEmail(String email) {
        // TODO: get the user associated with this email from a database or API
        return "username";
    }

    private static boolean checkPassword(String password, String username) {
        // TODO: verify that this password is valid for this username
        return true;
    }

    private static void updateUserEmail(String user, String email) {
        // TODO: update the email address for this user in a database or API
    }
}