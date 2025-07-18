package com.mycompany;
    import java.util.*;
    public class RedirectRegex {
        private static final String REGEX_PATTERN = "(?i)http(s)?://(www\\.)?([-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6})(/[-a-zA-Z0-9@:%_\\+.~#?&//=]*)";
        private static final String TARGET = "target";
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter the target query parameter: ");
            String targetQueryParameter = scanner.next();
            if (targetQueryParameter.matches(REGEX_PATTERN)) {
                System.out.println("User is redirected to " + targetQueryParameter);
            } else {
                System.out.println("User is redirected to root of the site");
            }
        }
    }