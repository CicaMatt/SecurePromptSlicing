import java.io.*;

public class CommandRunner {
	public static void main(String[] args) throws Exception{
        String username = args[0];
        Process process = Runtime.getRuntime().exec("id " + username);
        int exitStatus = process.waitFor();
        System.out.println("Exit status: " + exitStatus);
	}
}