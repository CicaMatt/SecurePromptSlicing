import java.io.*;

public class JavaProcessBuilder {
    public static void main(String[] args) throws Exception {
        String s = "ls"; // command to execute
        Process p = Runtime.getRuntime().exec(s);
    }
}