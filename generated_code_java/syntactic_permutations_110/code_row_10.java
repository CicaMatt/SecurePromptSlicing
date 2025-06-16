import java.io.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        Process process = Runtime.getRuntime().exec("id " + args[0]);
        int exitStatus = process.waitFor();
        System.out.println(exitStatus);
    }
}