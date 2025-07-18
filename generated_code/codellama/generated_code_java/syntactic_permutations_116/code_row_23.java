import java.util.*;

public class Main {
	public static void main(String[] args) {
		try {
			Process p = Runtime.getRuntime().exec("ls -l");
			BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
			String line = null;
			while ((line = in.readLine()) != null) {
				System.out.println(line);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}