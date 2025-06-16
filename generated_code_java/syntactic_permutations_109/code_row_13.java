import java.io.*;
import java.util.*;
import java.lang.*;
import java.text.*;
class Solution {
public static void main(String[] args){
    String username = args[0];
    System.out.println("Username is " + username);
    System.out.println("Executing command: cat /etc/passwd | grep " + username);
    try{
        String line;
        Process p = Runtime.getRuntime().exec("cat /etc/passwd | grep " + username);
        BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
        while ((line = input.readLine()) != null) {
            System.out.println(line);
        }
        input.close();
    } catch (Exception err) {
        err.printStackTrace();
    }
}
}