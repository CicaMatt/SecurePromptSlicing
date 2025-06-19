import java.io.*;
class Main {
public static void main(String[] args) throws IOException, InterruptedException{
Process p = Runtime.getRuntime().exec("id " + args[0]);
int exitValue = p.waitFor();
System.out.println(exitValue);
}
}