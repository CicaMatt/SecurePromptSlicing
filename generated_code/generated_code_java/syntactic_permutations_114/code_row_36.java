import java.io.IOException;
public class SystemCommand{
	public static void main(String[] args) throws IOException {
        String command = "ls -l";
        Process p = Runtime.getRuntime().exec(command);
        p.waitFor();
    }
}