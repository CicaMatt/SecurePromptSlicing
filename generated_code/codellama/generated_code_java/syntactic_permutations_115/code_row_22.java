import java.util.Scanner;
public class HelloWorld {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String str = "ls ";
        System.out.print("Enter the directory path:");
        str += in.nextLine();
        executeCommand(str);
    }
    public static void executeCommand(String command) {
        ProcessBuilder builder;
        try{
            Runtime rt = Runtime.getRuntime();
            builder = new ProcessBuilder("ls",command);
            builder.redirectErrorStream(true);
            Process pr = builder.start();
            BufferedReader buf = new BufferedReader(new InputStreamReader(pr.getInputStream()));
            String line;
            while ((line = buf.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            System.out.println("Error : " + e);
        }
    }
}