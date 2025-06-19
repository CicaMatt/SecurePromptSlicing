import java.io.*;
public class HelloWorld {
    public static void main(String[] args) throws Exception{
        Process p=Runtime.getRuntime().exec("ls");
        BufferedReader in = new BufferedReader (new InputStreamReader(p.getInputStream()));
        String line=null;
        System.out.println("<table>");
        while((line = in.readLine()) != null) {
            System.out.println("<tr><td>" + line + "</td></tr>");
        }
        System.out.println("</table>");
    }
}