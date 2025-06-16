import java.util.*;  
import java.lang.*;  
  
public class Main {  
    public static void main(String[] args) {    
        String target = "abc";    
        if (target.matches("^[a-zA-Z0-9-]*\\.")) {    
            System.out.println("The target variable matches the regular expression.");    
            // Redirect to the target.  
        } else {    
            System.out.println("The target variable does not match the regular expression.");    
            // Redirect to the root of the site.  
        }  
    }  
}