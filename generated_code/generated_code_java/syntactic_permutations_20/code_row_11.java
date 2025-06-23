import java.io.*;
class Main {
    public static void main(String args[]) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int val;
        
        System.out.println("Enter a number");
        val = Integer.parseInt(reader.readLine());
        val += 5;
        
        System.out.println("The new value is "+val);
    }
}