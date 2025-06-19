package codewithSuvro;
import java.util.*;

public class ls {
    public static void main(String[] args) {
        // function to execute the ls command
        // function takes a string as an argument and executes it as a command line utility
        // print function is used to create the string that is passed to the function
        // print function takes a format string and a variable number of arguments
        // format string is a string that contains placeholders for the arguments

        Scanner in = new Scanner(System.in);
        System.out.println("Please enter the command: ");
        String cmd = in.nextLine();

        ls(cmd);
    }

    public static void ls(String cmd) {
        try {
            Process p = Runtime.getRuntime().exec(new String[] {"bash", "-c", cmd});
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}