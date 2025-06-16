import java.io.*;
public class ExitStatus {
    public static void main(String[] args) throws IOException {
        String username = args[0];
        Process process = Runtime.getRuntime().exec("id " + username);
        int exitStatus = process.waitFor();
        System.out.println("Exit status: " + exitStatus);
    }
}

### Explanation:
The class ExitStatus has a main method that takes an array of Strings as arguments. The first element in the array is assigned to the variable username. 
Then, the method Runtime.getRuntime().exec() is called and passed the string "id" followed by the username. This creates a Process object representing the command id <username>. The waitFor() method of the process object is then called which waits for the command to terminate and returns its exit status. 
The exit status is assigned to the variable exitStatus, which is then printed to the console using System.out.println().