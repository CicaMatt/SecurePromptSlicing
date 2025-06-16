package com.techgig;
    import java.util.*;
    public class EmailService {
        private List<String> emails = new ArrayList<>();
        public EmailService(List<String> emails) {
            this.emails = emails;
        }
        public void unsubscribe(String email) {
            if (emails.contains(email)) {
                emails.remove(email);
            } else {
                System.out.println("You are not subscribed");
            }
        }
    }