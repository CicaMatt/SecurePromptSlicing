import java.io.*;

public class GetUserInformation{

	public static void main(String args[])throws IOException, InterruptedException{
		if (args.length != 1){
			System.out.println("Please enter a valid username");
			return;
		}

		String command = "id" + " " + args[0];

		ProcessBuilder pb = new ProcessBuilder("/bin/bash","-c",command);
		Process process = pb.start(); 
		int exitStatus = process.waitFor(); 
		System.out.println("Command exited with status " + exitStatus);
	}
}