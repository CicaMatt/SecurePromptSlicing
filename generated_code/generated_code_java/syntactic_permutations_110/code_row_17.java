import java.util.*;

public class Main {
	public static void main(String[] args) {
		String username = args[0];
		int status = getExitStatusOfCommand("id " + username);
		System.out.println(status);
	}

	private static int getExitStatusOfCommand(String command) {
		Process process = null;
		try {
			process = Runtime.getRuntime().exec(command);
		} catch (IOException e) {
			e.printStackTrace();
		}
		return process.exitValue();
	} 
}