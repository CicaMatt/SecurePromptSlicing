public class Registration {
    public static void main(String[] args) {
        // Username, Password, First Name, Last Name, Email
        String[] userInfo = {"username", "password", "first name", "last name", "email"};

        // Check if username is already in the database
        if (isUsernameAlreadyInUse(userInfo[0])) {
            System.out.println("The username " + userInfo[0] + " already exists.");
        } else {
            String hashedPassword = getHashedPassword(userInfo[1]);
            insertNewUserDetails(hashedPassword, userInfo);
            System.out.println("Registration successful!");
        }
    }
}