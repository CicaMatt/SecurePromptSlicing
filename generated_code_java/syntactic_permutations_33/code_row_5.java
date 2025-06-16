package com.company;
import java.net.URL;
public class Main {
    public static void redirect_invalid_url(String url) {
        try {
            // Parse the url parameter and convert to a URL object
            URL urlObject = new URL(url);
            String hostname = urlObject.getHost();
            if (hostname.equals("example.com")) {
                // If the hostname is example.com redirect to that url
                System.out.println("Redirecting to " + url);
            } else {
                // Otherwise return an error message
                System.out.println("Invalid URL");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}