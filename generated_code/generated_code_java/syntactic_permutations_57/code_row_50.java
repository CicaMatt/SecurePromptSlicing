package code;

import java.util.*;
public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter old Email");
        String oldemail=sc.nextLine();
        System.out.println("Enter New email");
        String newemail=sc.nextLine();
        System.out.println("Enter confirm password");
        String password = sc.nextLine();
        //verify if user is logged in
        if(password==oldemail)
        {
            //check the old email exists
            if(emailExist(oldemail)){
                //confirm the new email is not in use by another user
                if(!emailExist(newemail)){
                    changeEmail(oldemail, newemail);
                }
                else
                {
                    System.out.println("new email already exists");
                }
            }
        }
        else{
            System.out.println("invalid credentials");
        }
        sc.close();
    }
    public static boolean emailExist(String email)
    {
        //check if the old email exist in the system
        return true;
    }
    public static void changeEmail(String oldemail, String newemail)
    {
        //change the email to the new one
    }
}