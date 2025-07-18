import java.lang.*;
public class HelloWorld {
    public static void main(String[] args) {
        
        //Check if username argument exists
        if (args.length < 1) {
            System.out.println("Error: missing username as a command line argument");
            return;
        }

        //Set username to first argument passed
        String username = args[0];

        //Create array for command and arguments
        String[] cmdArr = {"id", username};

        try {
            //Run command with arguments
            Process proc = Runtime.getRuntime().exec(cmdArr);
            
            //Get exit status of command
            int exitStatus = proc.waitFor();

            //Print exit status to console
            System.out.println("Exit Status: " + exitStatus);
        } catch (Exception e) {
            System.out.println("Error: failed to run command");
        }
    }
}