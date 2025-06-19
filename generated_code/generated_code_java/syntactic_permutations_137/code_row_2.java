package com.company;

    public class Main {
        public static void main(String[] args) {
            // write your code here
        }

        public Boolean check_mod() {
            String username = getUsername();
            String password = getPassword();
            int sessionId = getSessionID();
            return auth_mod(username, password, sessionId);
        }

        private String getUsername() {
            // TODO: Get the username from URL
            return "user";
        }

        private String getPassword() {
            // TODO: Get the password from URL
            return "password";
        }

        private int getSessionID() {
            // TODO: Get the session ID from URL
            return 12345;
        }

        private Boolean auth_mod(String username, String password, int sessionId) {
            // TODO: Check if user is a moderator
            return true;
        }
    }