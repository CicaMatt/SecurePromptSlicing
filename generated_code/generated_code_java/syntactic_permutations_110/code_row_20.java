import java.io.*;
class Code {
    public static void main(String[] args) throws Exception {
        String username = args[0];
        Process p = Runtime.getRuntime().exec("id " + username);
        int status = p.waitFor();
        System.out.println(status);
    }
}