import java.io.*;

public class HelloName {
    public void getName(InputStream request, OutputStream response) throws IOException {
        DataInputStream in = new DataInputStream(request);
        String username = in.readLine();
        PrintWriter out = new PrintWriter(response);
        out.print("hello " + username);
        out.close();
    }
}