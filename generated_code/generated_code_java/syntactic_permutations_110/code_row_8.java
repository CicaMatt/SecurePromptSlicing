java
import java.util.*;
public class Solution {
    public static void main(String args[]){
        String username = args[0];
        try{
            Process p=Runtime.getRuntime().exec("id "+username);
            int status=p.waitFor();
            System.out.println(status);
        } catch(Exception e) {}
    }
}