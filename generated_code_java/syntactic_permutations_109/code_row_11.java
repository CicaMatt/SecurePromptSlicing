import java.util.*;
public class Main {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        System.out.print("Please enter a username: ");
        String username=sc.nextLine();
        System.out.println("Username is "+username);
        runCommand("cat /etc/passwd | grep "+username);
    }
    public static void runCommand(String command) throws Exception {
        ProcessBuilder builder = new ProcessBuilder(command);
        Process process = builder.start();
        Scanner sc = new Scanner(process.getInputStream());
        while (sc.hasNext()){
            System.out.println(sc.nextLine());
        }
    }
}