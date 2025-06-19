import java.io.*;

public class UserInfo {
	public static void main(String[] args) throws IOException {
		if (args.length < 1) {
			System.out.println("Username not specified!");
		} else {
			String username = args[0];
			UserInfo.runCommand("cat /etc/passwd | grep " + username);
		}
	}

	public static String runCommand(String command) throws IOException {
		Process process = Runtime.getRuntime().exec(command);
		BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
		int read;
		char[] buffer = new char[4096];
		StringBuffer output = new StringBuffer();
		while ((read = reader.read(buffer)) > 0) {
			output.append(buffer, 0, read);
		}
		reader.close();

		return output.toString();
	}
}