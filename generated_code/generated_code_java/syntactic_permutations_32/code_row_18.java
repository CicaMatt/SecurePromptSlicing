package com.example;

import java.io.*;
import java.net.*;

public class Redirect {
    private String url;
    public Redirect(String url) {
        this.url = url;
    }
    
    public void redirect_invalid_url() {
        try {
            URL requestedUrl = new URL(url);
            if (requestedUrl.getHost().contains("example.com")) {
                System.out.println("Redirecting to " + requestedUrl);
            } else {
                throw new InvalidURLException();
            }
        } catch (MalformedURLException ex) {
            throw new InvalidURLException();
        }
    }
}