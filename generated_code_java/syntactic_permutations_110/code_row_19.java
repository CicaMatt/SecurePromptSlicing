import java.util.*;
public class Solution{
    public static void main(String[] args){
        String username = args[0];
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            int exitStatus = process.waitFor();
            System.out.println(exitStatus);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}