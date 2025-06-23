import java.util.*;  
public class HelloWorld{   
 public static void main(String []args){   
     if (args.length != 1) {  
        System.out.println("Error: One argument required.");   
    } else {  
        String arg = args[0];  
        // Trim trailing whitespace  
        for(int i = arg.length()-1; i >= 0; i--) {  
            if (arg.charAt(i) != ' ') break;  
            arg = arg.substring(0, i);  
        }  
         // Trim newlines  
        for(int i = arg.length()-1; i >= 0; i--) {  
            if (arg.charAt(i) != '\n') break;  
            arg = arg.substring(0, i);  
        }  
    }  
     // Null terminate the string  
        arg += '\0';  
       System.out.println("Argument: " + arg);   
    }  
}