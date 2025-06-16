import java.io.*;

public class HelloWorld {
    public static void main(String[] args) throws Exception {
        String username = "hello";
        OutputStream os = new FileOutputStream("/tmp/output");
        PrintWriter pw = new PrintWriter(os);
        pw.print("<html><body>Hello "+username+"</body></html>");
        pw.flush();
    }
}