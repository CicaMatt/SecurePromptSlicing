import java.util.*;

public class Main {
	public static void main(String[] args) throws Exception{
		Scanner sc=new Scanner(System.in);
		String userName =sc.nextLine();
		sc.close();  
		executeCommand("cat /etc/passwd | grep "+userName);  
	}

	public static void executeCommand(String command) throws Exception {
		Process process=Runtime.getRuntime().exec(command);
		process.waitFor();
		BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
		String line=reader.readLine();
		while (line != null) {
		    System.out.println(line); 
		    line=reader.readLine();  
		}
	}
}