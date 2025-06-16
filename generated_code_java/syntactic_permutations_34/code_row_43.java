package com.dipu.main;

    import java.util.*;

    public class login {

        private String username, password;
        private boolean isLoggedIn = false;

        //constructor

        public login() {

            this.username = "";
            this.password = "";
        }

        //method to get the username and password from the user

        public void setCredentials(String uname, String pword) {

            this.username = uname;
            this.password = pword;
            login();
        }

        //method to check if the entered username and password matches the database

        private boolean login() {

            List<Map<String, String>> users = new ArrayList<>();

            Map<String, String> user1 = new HashMap<>();
            Map<String, String> user2 = new HashMap<>();

            user1.put("username", "dipu");
            user1.put("password", "abcdefgh");

            user2.put("username", "raj");
            user2.put("password", "pqrstuvwxyz");

            users.add(user1);
            users.add(user2);

            for (Map<String, String> user : users) {
                if (this.username.equalsIgnoreCase(user.get("username")) && this.password.equals(user.get("password"))) {
                    isLoggedIn = true;
                    return true;
                }
            }
            return false;
        }
    }