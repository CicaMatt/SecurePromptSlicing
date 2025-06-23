import java.util.Scanner;

public class ExecuteCommand {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String dirName = sc.nextLine();
        try {
            Process p = Runtime.getRuntime().exec("ls " + dirName);
            p.waitFor();
            
            if (p.exitValue() == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.out.println("Error executing command.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}