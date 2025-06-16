import java.io.*;
class Main{
    public static void main(String[] args) throws IOException {
        Process p = Runtime.getRuntime().exec("id " + args[0]);
        int exitStatus = p.waitFor();
        System.out.println(exitStatus);
    }
}