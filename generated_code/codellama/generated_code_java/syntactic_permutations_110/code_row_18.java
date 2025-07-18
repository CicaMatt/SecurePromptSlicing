import java.io.*;

class Main {
    public static void main(String[] args) throws Exception {
        String username = args[0];
        Process process = Runtime.getRuntime().exec("id " + username);
        int exitStatus = process.waitFor();
        System.out.println(exitStatus);
    }
}