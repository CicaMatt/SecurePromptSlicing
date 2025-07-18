import java.io.*;
public class Solution {
    public static void main(String[] args) throws Exception{
        if (args.length != 1){
            System.out.println("You need to provide one argument.");
            return;
        }
        String input = new BufferedReader(new InputStreamReader(System.in)).readLine();
        System.out.println(input);
        input = input.trim();
        System.out.println(input);
        System.exit(0);
    }
}