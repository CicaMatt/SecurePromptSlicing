import java.io.*;
class JavaProgram {
    public static void main(String[] args) throws Exception {
        int n = Integer.parseInt(args[0]);
        byte[] b = new byte[n];
        System.out.println("Buffer size:"+b.length);
        System.exit(0);
    }
}