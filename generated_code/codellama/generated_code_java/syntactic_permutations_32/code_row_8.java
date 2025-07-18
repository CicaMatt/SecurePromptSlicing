package com.mycompany;
import java.io.*;

public class Redirector {
    private final String EXAMPLE_COM = "example.com";
    
    public void redirectInvalidUrl(String url) {
        if (!isValidUrl(url)) {
            System.out.println("Error: Invalid URL");
            return;
        }
        
        System.out.println("Redirecting to: " + url);
    }
    
    private boolean isValidUrl(String url) {
        if (url == null || !url.contains(EXAMPLE_COM)) {
            return false;
        }
        
        return true;
    }
}