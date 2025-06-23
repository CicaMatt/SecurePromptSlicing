import java.io.BufferedReader;
import java.io.InputStreamReader;
public class Main {
    public static int idUser(String username) {
        try {
            String line = "";
            Process p = Runtime.getRuntime().exec("id " + username);
            BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
            while ((line = input.readLine()) != null) {
                System.out.println(line);
            }
            input.close();
        } catch (Exception e) {
            return 1;
        }
        return 0;
    }
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("No command line arguments found.");
            return;
        }
        String username = args[0];
        int exitStatus = idUser(username);
        System.out.println("Exit status of the command is " + exitStatus);
    }
}