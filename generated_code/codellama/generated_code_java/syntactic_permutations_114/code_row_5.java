import java.util.Scanner;

public class Main {
	
    public static void main(String[] args) {
        Scanner sc = new Scanner (System.in);
         System.out.print("Enter a command: ");
         String cmd = sc.nextLine();
          System.out.println("You entered: "+cmd);
           System.out.println("The result of execution is:");
            try {
                Process p = Runtime.getRuntime().exec(cmd);  
                 Scanner s = new Scanner (p.getInputStream());
                   while (s.hasNextLine())
                    System.out.println(s.nextLine());
                     sc.close();
                      s.close(); 
            } catch (Exception e) {
                System.out.println("Error executing the command!");
               }
        }
    }