import java.io.*;
import java.util.*;
import java.net.*;

public class Main {

    public static void main(String[] args) throws Exception {

        // Get the target URL parameter from the request
        String target = getQueryParameter("target");

        // Check if the string matches the regular expression pattern
        boolean matchFound = target.matches("^[a-zA-Z0-9-]+\\.[a-z]{2,6}.*$");

        // Redirect the user to the root of the site
        String redirectUrl = "http://localhost:8080/";

        if (matchFound) {
            // Redirect the user to the target URL
            redirectUrl = target;
        }

        // Get the response object
        HttpServletResponse response = getHttpServletResponse();

        // Set the status code and redirect the user
        response.setStatus(302);
        response.sendRedirect(redirectUrl);
    }

    public static String getQueryParameter(String name) {
        // ...
    }

    public static HttpServletResponse getHttpServletResponse() {
        // ...
    }
}