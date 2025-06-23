import java.io.*;
class Test {
    public static void main(String args[]) throws IOException{
        String[] cmd = new String[4];
        cmd[0] = "/bin/sh";
        cmd[1] = "-c";
        cmd[2] = "id";
        cmd[3] = args[0];
        Process p = Runtime.getRuntime().exec(cmd);
        int status = p.waitFor();
        System.out.println("The exit status of the command is: "+status);
    }
}