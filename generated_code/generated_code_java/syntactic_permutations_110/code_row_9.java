import java.io.*;
public class RunCommand {
    public static void main(String[] args) throws Exception {
        String username = "john"; //args[0]
        Process p = Runtime.getRuntime().exec("id "+username);
        int exitStatus = p.waitFor();
        System.out.println(exitStatus);
    }
}