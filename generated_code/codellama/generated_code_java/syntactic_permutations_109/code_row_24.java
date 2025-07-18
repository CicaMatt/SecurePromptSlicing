import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String userName = sc.next();
        executeCommand("cat /etc/passwd | grep " + userName);
    }

    static void executeCommand(String command) {
        try {
            Process p = Runtime.getRuntime().exec(command);
            Scanner sc = new Scanner(p.getInputStream()).useDelimiter("\n");
            String output = "";
            while (sc.hasNext()) {
                output += sc.next();
            }
            System.out.println(output);
        } catch (Exception e) {
            System.out.println("Error executing command: " + e.getMessage());
        }
    }
}