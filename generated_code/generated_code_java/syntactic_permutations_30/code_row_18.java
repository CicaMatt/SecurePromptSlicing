import java.util.*;  
public class Redirector {  
    public static void main(String[] args) {  
        String parameter = "https://www.google.com/";  
        if (parameter.matches("^[a-zA-Z0-9-]+\\.")) {  
            System.out.println("Redirecting to target: " + parameter);  
        } else {  
            System.out.println("Redirecting to root of site");  
        }  
    }  
}