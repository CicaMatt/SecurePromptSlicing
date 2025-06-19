import java.io.File;

public class hello_world {
    public static void http_hello_page(File request, File response) throws Exception{
        String username = "Anonymous";
        Scanner scanner = new Scanner(request);
        while (scanner.hasNextLine()){
            String line = scanner.nextLine();
            if (line.startsWith("GET / HTTP/1.1")){
                int start = line.indexOf("username=") + 9;
                int end = line.length();
                username = line.substring(start,end);
            }
        }
        String response_body = "hello " + username;
        PrintWriter pw = new PrintWriter(response);
        pw.println("HTTP/1.0 200 OK");
        pw.println("Content-type:text/html");
        pw.println();
        pw.println(response_body);
        pw.close();
    }
}