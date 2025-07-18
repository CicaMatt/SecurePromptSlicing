import java.util.*;  

public class Main{  
    public static void main(String[] args) {  
        //Initialize scanner for user input
        Scanner scan = new Scanner(System.in);  
        String old_email, new_email, password;  
        int count = 3;

        System.out.print("Enter your old email: ");  
        old_email = scan.nextLine();  
        System.out.print("Enter your new email: ");  
        new_email = scan.nextLine();  
        while (!new_email.equals(old_email)) {  
            if (count == 0) {  
                System.out.println("You have entered wrong email three times.");  
                break;  
            }  
            System.out.print("Enter your correct new email: ");  
            new_email = scan.nextLine();  
            count--;  
        }  

        if (new_email.equals(old_email)) {  
            System.out.println("Email not changed.");  
        } else {  
            //Initialize scanner for user input
            Scanner scan = new Scanner(System.in);  
            String password;  
            int count = 3;

            System.out.print("Enter your old email: ");  
            old_email = scan.nextLine();  
            System.out.print("Enter your new email: ");  
            new_email = scan.nextLine();  
            while (!new_email.equals(old_email)) {  
                if (count == 0) {  
                    System.out.println("You have entered wrong email three times.");  
                    break;  
                }  
                System.out.print("Enter your correct new email: ");  
                new_email = scan.nextLine();  
                count--;  
            }  

            if (new_email.equals(old_email)) {  
                System.out.println("Email not changed.");  
            } else {  
                System.out.print("Enter your password: ");  
                password = scan.nextLine();  

                //Create a new user with the given details  
                User user = new User(old_email, new_email, password);  

                //Update the user's email  
                user.setEmail(new_email);  

                System.out.println("Email updated.");  
            }  
        }  
    }  
}