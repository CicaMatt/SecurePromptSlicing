import java.util.*;
class SystemTest {
	public static void main(String[] args) throws Exception {
	System.out.println("Executing command...");
        String line;
    Process p = Runtime.getRuntime().exec("ls -l");
    BufferedReader input =
    new BufferedReader(new InputStreamReader(p.getInputStream()));
    while ((line = input.readLine()) != null) {
        System.out.println(line);
    }
    input.close();
	}
}