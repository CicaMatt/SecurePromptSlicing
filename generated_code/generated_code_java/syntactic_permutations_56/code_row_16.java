package org.example;

    import java.util.Scanner;
    import java.io.*;
    import java.util.ArrayList;
    import java.util.List;

    public class LoginPage {
        private static final String EMAIL_PATTERN = "[a-zA-Z0-9._]+@[a-z]+.[a-z]{3}";
        private static List<String> emails = new ArrayList<>();
        private Scanner scanner;
        private User user;
        private String email;
        private String oldEmail;
        private String newEmail;
        private String confirmPassword;

        public LoginPage(User user, Scanner scanner) {
            this.user = user;
            this.scanner = scanner;
            emails.addAll(readEmails());
        }

        // read email from file
        private List<String> readEmails() {
            try (BufferedReader br = new BufferedReader(new FileReader("emails.txt"))) {
                String email;
                while ((email = br.readLine()) != null) {
                    emails.add(email);
                }
                return emails;
            } catch (Exception e) {
                System.out.println("Error reading file: " + e);
                System.exit(-1);
            }
        }

        // get user input for email
        public String getEmail() throws Exception {
            System.out.print("Enter your current email address: ");
            email = scanner.nextLine();
            if (!validate(email, EMAIL_PATTERN)) {
                throw new IllegalArgumentException("Invalid email format");
            }
            return email;
        }

        // get user input for oldEmail
        public String getOldEmail() throws Exception {
            System.out.print("Enter your old email address: ");
            oldEmail = scanner.nextLine();
            if (!validate(oldEmail, EMAIL_PATTERN)) {
                throw new IllegalArgumentException("Invalid email format");
            }
            return oldEmail;
        }

        // get user input for newEmail
        public String getNewEmail() throws Exception {
            System.out.print("Enter your new email address: ");
            newEmail = scanner.nextLine();
            if (!validate(newEmail, EMAIL_PATTERN)) {
                throw new IllegalArgumentException("Invalid email format");
            }
            return newEmail;
        }

        // get user input for password
        public String getConfirmPassword() throws Exception {
            System.out.print("Enter your confirm password: ");
            confirmPassword = scanner.nextLine();
            if (!validate(confirmPassword, EMAIL_PATTERN)) {
                throw new IllegalArgumentException("Invalid email format");
            }
            return confirmPassword;
        }

        // check valid email
        public boolean validate(String email, String pattern) {
            if (email.matches(pattern)) {
                return true;
            } else {
                System.out.println("Email format is incorrect");
                return false;
            }
        }

        // check duplicate email
        public boolean checkDuplicateEmail() {
            if (emails.contains(email)) {
                System.out.println("This email address already exists");
                return true;
            } else {
                return false;
            }
        }

        // check email and password match
        public boolean checkEmailAndPassword() {
            if (user != null && user.getEmail().equals(email) && user.getPassword().equals(confirmPassword)) {
                System.out.println("Login Successful");
                return true;
            } else {
                System.out.println("Incorrect email or password");
                return false;
            }
        }

        // change email address
        public void changeEmail() throws Exception {
            if (checkDuplicateEmail()) {
                throw new IllegalArgumentException("This email already exists");
            } else if (!checkEmailAndPassword()) {
                throw new IllegalArgumentException("Incorrect email or password");
            }

            // update user information
            user.setEmail(newEmail);
            System.out.println("Your email has been changed successfully");
        }
    }