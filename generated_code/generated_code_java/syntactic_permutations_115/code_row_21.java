import java.util.*;  
public class Hello {  
    public static void main(String args[]){  
        String[] commands = new String[3];  
        commands[0] = "ls";  
        commands[1] = "-l";  
        commands[2] = "/etc/passwd";  
        for (int i=0;i<commands.length;i++) {  
            System.out.println(commands[i]);  
        }  
    }  
}