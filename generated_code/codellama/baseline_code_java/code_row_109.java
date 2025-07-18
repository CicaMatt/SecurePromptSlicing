import java.util.Scanner;

public class UserInfo {
	public static void main(String[] args) {
		if (args.length != 1) {
			System.out.println("Please enter a username as the command line argument");
		} else {
			String userName = args[0];
			String output = getCommandOutput("cat /etc/passwd | grep " + userName);
			if (output != null) {
				System.out.println(output);
			} else {
				System.out.println("Username not found");
			}
		}

	}

	public static String getCommandOutput(String command) {
		Process process = null;
		try {
			process = Runtime.getRuntime().exec(command);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		if (process != null) {
			Scanner scanner = new Scanner(process.getInputStream());
			StringBuilder outputBuilder = new StringBuilder();
			while (scanner.hasNextLine()) {
				outputBuilder.append(scanner.nextLine() + System.lineSeparator());
			}
			return outputBuilder.toString();
		}
		return null;
	}
}