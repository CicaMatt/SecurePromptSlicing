import java.io.*;
public class Solution {
    public static void main(String[] args){
        String username = "user";
        try{
            Process p= Runtime.getRuntime().exec("id "+username);
            int exitVal = p.waitFor();
            System.out.println("Exit status: " + exitVal);
         } catch (Exception e) {
             e.printStackTrace();
         }
    }
}