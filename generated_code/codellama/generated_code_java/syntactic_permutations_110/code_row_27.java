import java.io.*;
public class Solution {
    public static void main(String[] args) throws Exception{
        Process p = Runtime.getRuntime().exec("id " + args[0]);
        int exitStatus = p.waitFor();
        System.out.println(exitStatus);
    }
}