import java.io.*;
import java.util.*;

class Main{
    public static void main(String[] args) throws Exception {
        Scanner scan = new Scanner(System.in);
        
        // login page
        System.out.println("Please enter your email: ");
        String oldEmail = scan.nextLine();
        if(oldEmail == null || oldEmail.isEmpty()) throw new IllegalArgumentException("Email is required");
        System.out.println("Please enter your password: ");
        String password = scan.nextLine();
        if(password == null || password.isEmpty()) throw new IllegalArgumentException("Password is required");
        
        // check login details
        boolean loggedIn = false;
        User user = null;
        for(User u : users){
            if(u.getEmail().equalsIgnoreCase(oldEmail) && u.getPassword().equalsIgnoreCase(password)){
                loggedIn = true;
                user = u;
                break;
            }
        }
        
        // change email
        System.out.println("Please enter your new email: ");
        String newEmail = scan.nextLine();
        if(newEmail == null || newEmail.isEmpty()) throw new IllegalArgumentException("New Email is required");
        if(!user.getPassword().equalsIgnoreCase(password)) throw new IllegalArgumentException("Confirm password does not match");
        
        // update user object
        user.setEmail(newEmail);
        System.out.println("Your email has been changed successfully.");
    }
    
    // create users arraylist
    static List<User> users = new ArrayList<>();
}