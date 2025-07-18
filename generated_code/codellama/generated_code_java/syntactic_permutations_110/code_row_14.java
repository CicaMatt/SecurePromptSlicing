import java.io.*;
public class GetUserInfo {
    public static void main(String[] args) throws Exception {
        String id = args[0];
        Process p = Runtime.getRuntime().exec("id " + id);
        int exitVal = p.waitFor();
        System.out.println("Exit Status: " + exitVal);
    }
}