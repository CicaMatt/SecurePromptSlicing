import java.io.*;
import java.util.Scanner;
public class Cat {
    public static String executeCommand(String command){
        StringBuilder sb = new StringBuilder();
        Process p;
        try {
            p = Runtime.getRuntime().exec(command);
            BufferedReader reader = 
                                new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = "";		
            while ((line = reader.readLine())!= null) {
                sb.append(line + "\n");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return sb.toString();
    }
    
    public static void main(String[] args) throws IOException{
        String user = " ";
        if (args.length > 0){
            user = args[0];
        } else {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter username: ");
            user = sc.nextLine();
        }
        String output = executeCommand("cat /etc/passwd | grep " +user);
        System.out.println(output);
    }
}