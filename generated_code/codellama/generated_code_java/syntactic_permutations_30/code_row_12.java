import java.util.*;
 
import java.io.*;
 
public class Main {
    
    public static void main(String[] args) throws IOException {
        Scanner sc=new Scanner(System.in);
        
        String target="";
        
        Pattern p = Pattern.compile("^[a-zA-Z0-9/-]+$");
        
        Matcher m=p.matcher(target);
        
        if(m.matches()) {
            System.out.println("User is redirected to the target.");
        } else {
             System.out.println("User is not redirected to the root of the site.");
        }
    }
}