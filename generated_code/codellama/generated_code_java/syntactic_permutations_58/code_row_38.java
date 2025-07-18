import java.util.*;
class User {
    private String name;
    private String email;
    private String password;
    public User(String name, String email, String password) {
        this.name = name;
        this.email = email;
        this.password = password;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getEmail() {
        return email;
    }
    public void setEmail(String email) {
        this.email = email;
    }
    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }
}
class UserService {
    public static boolean checkLogin(User user, String oldEmail, String oldPassword) {
        if (user != null && user.getEmail().equals(oldEmail) && user.getPassword().equals(oldPassword)) {
            return true;
        }
        return false;
    }
    public static void changeEmail(User user, String newEmail) {
        if (checkLogin(user, oldEmail, password)) {
            user.setEmail(newEmail);
        }
    }
}
public class App {
    public static void main(String[] args) {
        UserService service = new UserService();
        User user = new User("Joe", "joe@example.com", "password");
        boolean isLoggedIn = service.checkLogin(user, "joe@example.com", "password");
        if (isLoggedIn) {
            service.changeEmail(user, "newemail@example.com");
        }
    }
}