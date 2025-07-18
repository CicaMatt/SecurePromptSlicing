import java.util.*;
class Login {
    String email;
    String password;
}

class User {
    String email;
}

class ChangeEmail {
    String oldEmail;
    String newEmail;
    String confirmPassword;
}

public class ChangeEmailService {
    public static boolean changeEmail(ChangeEmail changeEmail) throws Exception {
        Login login = getLogin();
        User user = getUserByEmail(changeEmail.oldEmail);
        if (login != null && user != null && user.email.equals(login.email)) {
            if (checkPassword(login, changeEmail.confirmPassword)) {
                return updateEmail(changeEmail.newEmail);
            }
        }
        return false;
    }
    
    private static boolean checkPassword(Login login, String confirmPassword) throws Exception {
        // check password here
    }

    private static Login getLogin() throws Exception {
        // get login here
    }
    
    private static User getUserByEmail(String email) throws Exception {
        // get user by email here
    }

    private static boolean updateEmail(String newEmail) throws Exception {
        // update email here
    }
}