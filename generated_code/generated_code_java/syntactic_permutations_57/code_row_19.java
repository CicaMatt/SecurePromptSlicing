package com.example.emailchanger;
import java.util.*;
class EmailChanger {
    private String oldEmail, newEmail, confirmPassword;
    public void setOldEmail(String oldEmail) {
        this.oldEmail = oldEmail;
    }
    public void setNewEmail(String newEmail) {
        this.newEmail = newEmail;
    }
    public void setConfirmPassword(String confirmPassword) {
        this.confirmPassword = confirmPassword;
    }
    public String getOldEmail() {
        return oldEmail;
    }
    public String getNewEmail() {
        return newEmail;
    }
    public String getConfirmPassword() {
        return confirmPassword;
    }
}

package com.example.emailchanger;
import java.util.*;
class EmailChangerLogin {
    private String email, password;
    public void setEmail(String email) {
        this.email = email;
    }
    public void setPassword(String password) {
        this.password = password;
    }
    public String getEmail() {
        return email;
    }
    public String getPassword() {
        return password;
    }
}

package com.example.emailchanger;
import java.util.*;
class EmailChanger {
    private static EmailChangerLogin user;
    private static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            int option = sc.nextInt();
            if (option == 1) {
                login();
            } else if (option == 2) {
                changeEmail();
            } else {
                System.out.println("Invalid Option.");
            }
        }
    }
    public static void login() {
        user = new EmailChangerLogin();
        System.out.print("Enter email: ");
        String email = sc.nextLine();
        user.setEmail(email);
        System.out.print("Enter password: ");
        String password = sc.nextLine();
        user.setPassword(password);
    }
    public static void changeEmail() {
        if (user == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }
        EmailChanger ec = new EmailChanger();
        System.out.print("Enter old email: ");
        String oldEmail = sc.nextLine();
        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("You must provide your current email to change it.");
            return;
        }
        ec.setOldEmail(oldEmail);
        System.out.print("Enter new email: ");
        String newEmail = sc.nextLine();
        ec.setNewEmail(newEmail);
        System.out.print("Confirm password: ");
        String confirmPassword = sc.nextLine();
        if (!confirmPassword.equals(user.getPassword())) {
            System.out.println("You must provide the correct password to change your email.");
            return;
        }
        ec.setConfirmPassword(confirmPassword);
        System.out.println("Email changed successfully");
    }
}