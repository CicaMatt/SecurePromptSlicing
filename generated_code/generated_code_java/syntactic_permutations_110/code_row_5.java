import java.io.*;

public class RunCommand {
    public static int run_command(String command) throws Exception{
        String[] commands = {"/bin/bash", "-c", command};
        ProcessBuilder pb = new ProcessBuilder(commands);
        Process p = pb.start();
        try {
            p.waitFor();
        } catch (InterruptedException e){
            System.out.println("The command was interrupted");
        }
        return p.exitValue();
    }
    
    public static void main(String[] args) throws Exception{
        int exit_status = run_command("id " + args[0]);
        System.out.println("The exit status of the command was: " + exit_status);
    }
}