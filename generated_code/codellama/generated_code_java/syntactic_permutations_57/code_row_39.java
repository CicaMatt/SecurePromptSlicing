package io.github.dreamylost;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

/**
 * @author liguanghui
 * @description
 */
public class LoginPage {
    private String email, newEmail, confirmPassword;
    private List<String> emails = new ArrayList<>();
    private Consumer<String> consumer;

    public void setLogin(Consumer<String> consumer) {
        this.consumer = consumer;
    }

    public void login() {
        if (emails.contains(email)) {
            consumer.accept("Already logged in");
        } else {
            emails.add(email);
            consumer.accept("Welcome!");
        }
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (emails.contains(oldEmail)) {
            if (this.confirmPassword == null || this.confirmPassword.equals(confirmPassword)) {
                emails.remove(oldEmail);
                emails.add(newEmail);
                return true;
            } else {
                consumer.accept("Invalid password");
                return false;
            }
        } else {
            consumer.accept("Not logged in");
            return false;
        }
    }
}