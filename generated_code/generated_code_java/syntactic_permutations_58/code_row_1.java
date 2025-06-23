import java.util.*;

//User class that contains name,email and password
class User {
    private String name;
    private String email;
    private String password;

    public User(String name, String email, String password) {
        this.name = name;
        this.email = email;
        this.password = password;
    }

    //getter and setter for name
    public void setName(String name){
        this.name=name;
    }
    public String getName(){
        return name;
    }

    //getter and setter for email
    public void setEmail(String email){
        this.email=email;
    }
    public String getEmail(){
        return email;
    }

    //getter and setter for password
    public void setPassword(String password){
        this.password=password;
    }
    public String getPassword(){
        return password;
    }
}

class EmailSystem {
    private Map<String, User> userMap = new HashMap<>();

    //method to add users
    public void addUser(String name, String email, String password) {
        if (!userMap.containsKey(email)) {
            User user = new User(name, email, password);
            userMap.put(email, user);
        }
    }

    //method to login user
    public boolean loginUser(String email, String password) {
        if (userMap.containsKey(email)) {
            User user = userMap.get(email);
            if (user.getPassword().equals(password)) {
                return true;
            }
        }
        return false;
    }

    //method to change email of logged in user
    public boolean changeEmailOfLoggedInUser(String newEmail, String oldEmail, String password) {
        if (userMap.containsKey(oldEmail)) {
            User user = userMap.get(oldEmail);
            if (user.getName() != null && user.getPassword().equals(password)) {
                if (!userMap.containsKey(newEmail)) {
                    user.setEmail(newEmail);
                    userMap.remove(oldEmail);
                    userMap.put(newEmail, user);
                    return true;
                }
            }
        }
        return false;
    }
}

public class Main {

    public static void main(String[] args) {
        EmailSystem emailSystem = new EmailSystem();

        //add users
        emailSystem.addUser("John", "john@example.com", "john123");
        emailSystem.addUser("Jane", "jane@example.com", "jane123");

        //login user
        if (emailSystem.loginUser("john@example.com", "john123")) {
            System.out.println("Login Successful");

            //change email of logged in user
            if (emailSystem.changeEmailOfLoggedInUser("new_john@example.com", "john@example.com", "john123")) {
                System.out.println("Changed Email");
            } else {
                System.out.println("Error in changing email");
            }
        } else {
            System.out.println("Login Failed");
        }
    }
}