import java.io.*;
import java.util.*;
import java.net.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Redirect {
    private final static Pattern urlRegex = Pattern.compile("http(s)?://([\\w-]+\\.)+[a-z]{2,4}/?");
    public static void main(String[] args) throws Exception {
        Matcher urlMatch = urlRegex.matcher("https://www.example.com/test/");
        if (urlMatch.find()) {
            System.out.println("Redirecting to: " + urlMatch);
        } else {
            System.out.println("Redirecting to: https://www.example.com");
        }
    }
}