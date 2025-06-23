package com.login.page;

import java.util.*;
import java.io.*;

public class LoginPage {
    private String username;
    private String oldEmail;
    private String newEmail;
    private String confirmPassword;

    public void setUsername(String username) {
        this.username = username;
    }

    public void setOldEmail(String oldEmail) {
        this.oldEmail = oldEmail;
    }

    public void setNewEmail(String newEmail) {
        this.newEmail = newEmail;
    }

    public void setConfirmPassword(String confirmPassword) {
        this.confirmPassword = confirmPassword;
    }

    public String getUsername() {
        return username;
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