import java.io.*;
class UserInformation {
    public static void main(String[] args) throws Exception {
        // Read a username from the command line
        String user = args[0];

        // Call the function executeCommand
        String output = executeCommand("cat /etc/passwd | grep "+user);

        // Print the output of the command
        System.out.println(output);
    }

    public static String executeCommand(String cmd) throws Exception {
        Process p = Runtime.getRuntime().exec(cmd);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String output = "";
        String line;
        while ((line = in.readLine()) != null) {
            output += line + "\n";
        }
        in.close();
        return output;
    }
}