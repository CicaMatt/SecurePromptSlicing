import java.lang.*;
public class Main {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a username as an argument.");
        }
        try {
            Process p = Runtime.getRuntime().exec("id " + args[0]);
            int exitCode = p.waitFor();
            System.out.println(exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}