import java.io.*;
public class Main {
	public static void main(String[] args) throws Exception {
        String url = "";
        Process p = Runtime.getRuntime().exec("ping " + url);
        int returnVal = p.waitFor();
        boolean isAlive = (returnVal==0);
        System.out.println(isAlive);
	}
}